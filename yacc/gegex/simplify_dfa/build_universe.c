
#if 0

#include <assert.h>

#include <debug.h>

#include <tree/of_gegexes/add.h>

#include "../state/struct.h"

#include "build_universe.h"

void gegex_simplify_dfa_build_universe(
	struct gegextree* universe,
	struct gegex* node)
{
	ENTER;
	
	dpv(node);
	
	if (gegextree_add(universe, node))
	{
		size_t i, n;
		
		assert(!node->lambda_transitions.n);
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			gegex_simplify_dfa_build_universe(universe, node->transitions.data[i]->to);
		}
		
		for (i = 0, n = node->grammar_transitions.n; i < n; i++)
		{
			gegex_simplify_dfa_build_universe(universe, node->grammar_transitions.data[i]->to);
		}
	}
	
	EXIT;
}








#endif
