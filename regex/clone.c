
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/safe_insert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "clone.h"

struct mapping
{
	struct regex* old; // must be the first
	struct regex* new;
};

static int compare(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

struct memory_arena;

static struct regex* clone_helper(
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct regex* old)
{
	struct avl_node_t* node;
	ENTER;
	
	if ((node = avl_search(mappings, &old)))
	{
		// *out = node->item->new;
		TODO;
	}
	else
	{
		struct regex* new = new_regex(arena);
		
		new->is_accepting = old->is_accepting;
		
		struct mapping* mapping = smalloc(sizeof(*mapping));
		
		mapping->old = old;
		mapping->new = new;
		
		safe_avl_insert(mappings, mapping);
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			regex_add_transition(
				/* from: */ new,
				/* arena */ arena,
				/* value: */ ele->value,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* in: */ ele->to));
		}
		
		// for each lambda transition:
		for (i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			
			TODO;
		}
		
		// for default transition:
		if (old->default_transition_to)
		{
			TODO;
		}
		
		EXIT;
		return new;
	}
}

struct regex* regex_clone(
	struct memory_arena* arena,
	struct regex* in)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare, free);
	
	struct regex* retval = clone_helper(mappings, arena, in);
	
	avl_free_tree(mappings);
	
	EXIT;
	return retval;
}














