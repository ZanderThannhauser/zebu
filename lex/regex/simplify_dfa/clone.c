
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <tree/of_regexes/struct.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"

#include "same_as_node/struct.h"

#include "clone.h"

static struct mapping {
	struct regex* old; // must be the first
	struct regex* new;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
}* new_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* old, struct regex* new)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct mapping* this = arena_malloc(arena, sizeof(*this));
	#else
	struct mapping* this = malloc(sizeof(*this));
	#endif
	
	this->old = old, this->new = new;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
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
	struct mapping* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

static struct regex* find(struct avl_tree_t* connections, struct regex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

static struct regex* clone_helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* mappings,
	struct avl_tree_t* connections,
	struct regex* old)
{
	struct avl_node_t* node;
	struct mapping* mapping;
	ENTER;
	
	dpv(old);
	
	if ((node = avl_search(mappings, &old)))
	{
		EXIT;
		return (mapping = node->item)->new;
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
		avl_insert(mappings, new_mapping(arena, old, new));
		#else
		avl_insert(mappings, new_mapping(old, new));
		#endif
		
		// calculate default transition first,
		if (old->default_transition_to)
		{
			struct regex* cloneme = find(connections, old->default_transition_to);
			
			dpv(cloneme);
			
			regex_set_default_transition(
				/* from: */ new,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ cloneme));
		}
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			struct regex* cloneme = find(connections, ele->to);
			
			struct regex* to = clone_helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* mappings: */ mappings,
				/* connections: */ connections,
				/* in: */ cloneme);
			
			// don't add the transition if the default already covers it
			if (to != new->default_transition_to)
			{
				regex_add_transition(
					/* from: */ new,
					/* value: */ ele->value,
					/* to: */ to);
			}
		}
		
		// EOF transitions?
		if (old->EOF_transition_to)
		{
			struct regex* cloneme = find(connections, old->EOF_transition_to);
			
			dpv(cloneme);
			
			regex_set_EOF_transition(
				/* from: */ new,
				/* to */ clone_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ cloneme));
		}
		
		EXIT;
		return new;
	}
}

struct regex* regex_simplify_dfa_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* connections,
	struct regex* original_start)
{
	ENTER;
	
	dpv(original_start);
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	#endif
	
	struct regex* cloneme = find(connections, original_start);
	
	dpv(cloneme);
	
	#ifdef WITH_ARENAS
	struct regex* new_start = clone_helper(arena, mappings, connections, cloneme);
	#else
	struct regex* new_start = clone_helper(mappings, connections, cloneme);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















