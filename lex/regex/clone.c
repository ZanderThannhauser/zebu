
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>
#include <avl/alloc_tree.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_lambda_transition.h"
#include "state/set_default_transition.h"

#include "clone.h"

struct mapping
{
	struct regex* old; // must be the first
	struct regex* new;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

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
	ENTER;
	
	#ifdef WITH_ARENAS
	struct mapping* const m = ptr;
	arena_dealloc(m->arena, m);
	#else
	free(ptr);
	#endif
	
	EXIT;
}

struct memory_arena;

static struct regex* clone_helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* mappings,
	struct regex* old)
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
		struct regex* new = new_regex(arena);
		#else
		struct regex* new = new_regex();
		#endif
		
		new->is_accepting = old->is_accepting;
		
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
			
			regex_add_transition(
				/* from: */ new,
				/* value: */ ele->value,
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
			regex_add_lambda_transition(
				/* from: */ new,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* in: */ old->lambda_transitions.data[i]));
		}
		
		// for default transition:
		if (old->default_transition_to)
		{
			regex_set_default_transition(
				/* from: */ new,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* in: */ old->default_transition_to));
		}
		
		EXIT;
		return new;
	}
}

struct regex* regex_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* in)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	#endif
	
	#ifdef WITH_ARENAS
	struct regex* retval = clone_helper(arena, mappings, in);
	#else
	struct regex* retval = clone_helper(mappings, in);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return retval;
}


struct clone_nfa_bundle regex_clone_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* start,
	struct regex* end)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = new_avl_tree(compare, free);
	
	struct regex* new_start = clone_helper(mappings, arena, start);
	struct regex* new_end = clone_helper(mappings, arena, end);
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct clone_nfa_bundle) {new_start, new_end};
	#endif
}























