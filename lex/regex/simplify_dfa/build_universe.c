

#include <assert.h>

#include <debug.h>

#include <set/regex/add.h>

#include "../state/struct.h"
#include "../state/foreach_transition.h"

#include "build_universe.h"

void regex_simplify_dfa_build_universe(
	struct regexset* universe,
	struct regex* node)
{
	ENTER;
	
	dpv(node);
	
	if (regexset_add(universe, node))
	{
		size_t i, n;
		
		regex_foreach_transition(node, ({
			void runme(unsigned char _, struct regex* to)
			{
				regex_simplify_dfa_build_universe(universe, to);
			}
			runme;
		}));
		
		if (node->default_transition_to)
		{
			regex_simplify_dfa_build_universe(universe, node->default_transition_to);
		}
		
		if (node->EOF_transition_to)
		{
			regex_simplify_dfa_build_universe(universe, node->EOF_transition_to);
		}
	}
	
	EXIT;
}








