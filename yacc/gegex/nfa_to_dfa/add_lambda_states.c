
#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <tree/of_gegexes/add.h>

#include "add_lambda_states.h"

void gegex_add_lamda_states(
	struct gegextree* set, struct gegex* ele)
{
	ENTER;
	
	dpv(ele);
	
	if (gegextree_add(set, ele))
	{
		unsigned i, n;
		for (i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			gegex_add_lamda_states(set,
				ele->lambda_transitions.data[i]);
		}
	}
	
	EXIT;
}
















