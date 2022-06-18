
#include <avl/avl.h>

#include <debug.h>

#include <regex/state/struct.h>

#include "../phase_counter.h"

#include "helper.h"

void simplify_dfa_helper(
	struct avl_tree_t* unique_nodes,
	struct regex* node)
{
	ENTER;
	
	if (node->phase != phase_counter)
	{
		size_t i, n;
		
		node->phase = phase_counter;
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			simplify_dfa_helper(unique_nodes, node->transitions.data[i]->to);
		}
		
		if (node->default_transition_to)
		{
			// call self
			TODO;
		}
		
		if (!avl_search(unique_nodes, node))
		{
			avl_insert(unique_nodes, node);
		}
	}
	
	EXIT;
}









