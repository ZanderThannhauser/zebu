
#include <avl/avl.h>
#include <avl/new.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "clone.h"

struct mapping
{
	struct regex_state* old; // must be the first
	struct regex_state* new;
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

static int clone_helper(
	struct regex_state** out,
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct regex_state* old)
{
	int error = 0;
	struct avl_node_t* node;
	ENTER;
	
	if ((node = avl_search(mappings, &old)))
	{
		// *out = node->item->new;
		TODO;
	}
	else
	{
		struct regex_state* new;
		
		error = new_regex_state(&new, arena);
		
		struct mapping* mapping;
		
		// allocate mapping:
		if (!error)
		{
			new->is_accepting = old->is_accepting;
			
			error = smalloc((void**) &mapping, sizeof(*mapping));
		}
		
		// insert mapping:
		if (!error)
		{
			assert(mapping);
			
			mapping->old = old;
			mapping->new = new;
			
			if (!avl_insert(mappings, mapping))
			{
				TODO;
				error = e_out_of_memory;
			}
		}
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; !error && i < n; i++)
		{
			struct regex_state* new_dest;
			struct transition* ele = old->transitions.data[i];
			
			error = 0
				?: clone_helper(
					/* out: */ &new_dest,
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* in: */ ele->to)
				?: regex_state_add_transition(
					/* from: */ new,
					/* arena */ arena,
					/* value: */ ele->value,
					/* to */ new_dest);
		}
		
		// for each lambda transition:
		for (i = 0, n = old->lambda_transitions.n; !error && i < n; i++)
		{
			
			TODO;
		}
		
		// for default transition:
		if (!error && old->default_transition_to)
		{
			TODO;
		}
		
		*out = new;
	}
	
	EXIT;
	return error;
}


int regex_clone(
	struct regex_state** out,
	struct memory_arena* arena,
	struct regex_state* in)
{
	int error = 0;
	ENTER;
	
	struct avl_tree_t* mappings = NULL;
	
	error = 0
		?: new_avl_tree(&mappings, compare, free)
		?: clone_helper(out, mappings, arena, in);
	
	avl_free_tree(mappings);
	
	EXIT;
	return error;
}














