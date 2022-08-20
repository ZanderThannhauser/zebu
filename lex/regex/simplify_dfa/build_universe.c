

#include <assert.h>

#include <debug.h>

#include <tree/of_regexes/add.h>

#include "../state/struct.h"

#include "build_universe.h"

void simplify_dfa_build_universe(
	struct regextree* universe,
	struct regex* node)
{
	ENTER;
	
	dpv(node);
	
	if (regextree_add(universe, node))
	{
		size_t i, n;
		
		assert(!node->lambda_transitions.n);
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			simplify_dfa_build_universe(universe, node->transitions.data[i]->to);
		}
		
		if (node->default_transition_to)
		{
			simplify_dfa_build_universe(universe, node->default_transition_to);
		}
		
		if (node->EOF_transition_to)
		{
			simplify_dfa_build_universe(universe, node->EOF_transition_to);
		}
	}
	
	EXIT;
}









