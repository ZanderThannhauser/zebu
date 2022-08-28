
#if 0
#include <assert.h>

#include <debug.h>

#include <tree/of_lstates/add.h>

#include "../state/struct.h"

#include "build_universe.h"

void minimize_lexer_build_universe(
	struct lstatetree* universe,
	struct lex_state* node)
{
	ENTER;
	
	dpv(node);
	
	if (lstatetree_add(universe, node))
	{
		size_t i, n;
		
		for (i = 0, n = node->transitions.n; i < n; i++)
		{
			minimize_lexer_build_universe(universe, node->transitions.data[i]->to);
		}
		
		if (node->default_transition_to)
		{
			minimize_lexer_build_universe(universe, node->default_transition_to);
		}
		
		if (node->EOF_transition_to)
		{
			minimize_lexer_build_universe(universe, node->EOF_transition_to);
		}
	}
	
	EXIT;
}








#endif
