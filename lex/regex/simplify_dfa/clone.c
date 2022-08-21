
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <tree/of_regexes/struct.h>

#include <avl/search.h>
#include <avl/free_tree.h>

/*#include <memory/smalloc.h>*/

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
}* new_mapping(struct regex* old, struct regex* new)
{
	TODO;
	#if 0
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
	return this;
	#endif
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

static struct regex* find(struct avl_tree_t* connections, struct regex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	assert(node);
	struct same_as_node* sa = node->item;
	assert(sa->set->n);
	return sa->set->tree->head->item;
}

static struct regex* clone_helper(
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct avl_tree_t* connections,
	struct regex* old)
{
	struct avl_node_t* node;
	struct mapping* mapping;
	ENTER;
	
	TODO;
	#if 0
	dpv(old);
	
	if ((node = avl_search(mappings, &old)))
	{
		EXIT;
		return (mapping = node->item)->new;
	}
	else
	{
		struct regex* new = new_regex(arena);
		
		new->is_accepting = old->is_accepting;
		
		safe_avl_insert(mappings, new_mapping(old, new));
		
		// calculate default transition first,
		if (old->default_transition_to)
		{
			struct regex* cloneme = find(connections, old->default_transition_to);
			
			dpv(cloneme);
			
			regex_set_default_transition(
				/* from: */ new,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
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
				/* mappings: */ mappings,
				/* arena: */ arena,
				/* connections: */ connections,
				/* in: */ cloneme);
			
			// don't add the transition if the default already covers it
			if (to != new->default_transition_to)
			{
				regex_add_transition(
					/* from: */ new,
					/* arena */ arena,
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
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* connections: */ connections,
					/* in: */ cloneme));
		}
		
		EXIT;
		return new;
	}
	#endif
}

struct regex* regex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	dpv(original_start);
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = new_avl_tree(compare_mappings, free);
	
	struct regex* cloneme = find(connections, original_start);
	
	dpv(cloneme);
	
	struct regex* new_start = clone_helper(
		mappings, arena, connections, cloneme);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
	#endif
}


















