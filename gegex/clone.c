
#include <debug.h>

#include <quack/struct.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_grammar_transition.h"

#include "dotout.h"
#include "clone.h"

struct mapping
{
	struct gegex* old; // must be the first
	struct gegex* new;
};

static struct mapping* new_mapping(struct gegex* old, struct gegex* new)
{
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static void free_mapping(void* ptr)
{
	struct mapping* const this = ptr;
	ENTER;
	
	free(this);
	
	EXIT;
}

struct gegex* gegex_clone(struct gegex* original_start)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct gegex* new_start = new_gegex();
	
	{
		struct mapping* mapping = new_mapping(original_start, new_start);
		avl_insert(mappings, mapping);
		quack_append(todo, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: gegex-clone: %u of %u (%.2f%%)\r", argv0,
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct gegex* const old = mapping->old;
		struct gegex* const new = mapping->new;
		
		new->is_reduction_point = old->is_reduction_point;
		
		// for each transition:
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct gegex_transition* const ele = old->transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &ele->to);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_transition(new, ele->token, ele->tags, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(ele->to, subnew);
				
				gegex_add_transition(new, ele->token, ele->tags, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		// for each lambda transition:
		for (unsigned i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = old->grammar_transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &ele->to);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_grammar_transition(new, ele->grammar, ele->tags, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(ele->to, subnew);
				
				gegex_add_grammar_transition(new, ele->grammar, ele->tags, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		// for each lambda transition:
		for (unsigned i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			TODO;
			#if 0
			struct gegex* const subold = old->lambda_transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_lambda_transition(new, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(subold, subnew);
				
				gegex_add_lambda_transition(new, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
			#endif
		}
		
		#ifdef DOTOUT
		gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
		#endif
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}



#if 0
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include <arena/strdup.h>
#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_grammar_transition.h"
#include "state/add_lambda_transition.h"

#include "clone.h"

struct memory_arena;

static struct gegex* clone_helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* mappings,
	struct gegex* old)
{
	struct avl_node_t* node;
	ENTER;
	
	if ((node = avl_search(mappings, &old)))
	{
		struct mapping* mapping = node->item;
		
		EXIT;
		return mapping->new;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct gegex* new = new_gegex(arena);
		#else
		struct gegex* new = new_gegex();
		#endif
		
		new->is_reduction_point = old->is_reduction_point;
		
		#ifdef WITH_ARENAS
		struct mapping* mapping = arena_malloc(arena, sizeof(*mapping));
		#else
		struct mapping* mapping = malloc(sizeof(*mapping));
		#endif
		
		mapping->old = old;
		mapping->new = new;
		
		#ifdef WITH_ARENAS
		mapping->arena = arena;
		#endif
		
		avl_insert(mappings, mapping);
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			dpv(ele->token);
			
			gegex_add_transition(
				/* from: */ new,
				/* value: */ ele->token,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* in: */ ele->to));
		}
		
		for (i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const ele = old->grammar_transitions.data[i];
			
			#ifdef WITH_ARENAS
			char* grammar = arena_strdup(arena, ele->grammar);
			#else
			char* grammar = strdup(ele->grammar);
			#endif
			
			gegex_add_grammar_transition(
				/* from: */ new,
				/* value: */ grammar,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* in: */ ele->to));
		}
		
		// for each lambda transition:
		for (i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			gegex_add_lambda_transition(
				/* from: */ new,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* in: */ old->lambda_transitions.data[i]));
		}
		
		EXIT;
		return new;
	}
}

struct gegex* gegex_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* in)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = new_avl_tree(compare, free);
	
	struct gegex* retval = clone_helper(mappings, arena, in);
	
	avl_free_tree(mappings);
	
	EXIT;
	return retval;
	#endif
}


struct gbundle gegex_clone_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	#endif
	
	#ifdef WITH_ARENAS
	struct gegex* new_start = clone_helper(arena, mappings, start);
	struct gegex* new_end = clone_helper(arena, mappings, end);
	#else
	struct gegex* new_start = clone_helper(mappings, start);
	struct gegex* new_end = clone_helper(mappings, end);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct gbundle) {new_start, new_end};
}
#endif






















