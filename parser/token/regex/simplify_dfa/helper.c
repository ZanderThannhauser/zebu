
#include <avl/avl.h>

#include <debug.h>

#include "../state/struct.h"

#include "../phase_counter.h"

#include "helper.h"

void simplify_dfa_helper(
	struct avl_tree_t* unique_nodes,
	struct regex* node)
{
	ENTER;
	
	dpv(node);
	
	if (node->phase != phase_counter)
	{
		size_t i, n;
		
		node->phase = phase_counter;
		
		assert(!node->lambda_transitions.n);
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			dpv(node->transitions.data[i]->value);
			simplify_dfa_helper(unique_nodes, node->transitions.data[i]->to);
		}
		
		if (node->default_transition_to)
		{
			ddprintf("has default\n");
			simplify_dfa_helper(unique_nodes, node->default_transition_to);
		}
		
		if (!avl_search(unique_nodes, node))
		{
			ddprintf("looks new, adding...\n");
			avl_insert(unique_nodes, node);
		}
	}
	
	EXIT;
}









