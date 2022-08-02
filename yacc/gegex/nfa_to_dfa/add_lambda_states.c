
#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <set/of_gegexes/contains.h>
#include <set/of_gegexes/add.h>

#include "add_lambda_states.h"

void gegex_add_lamda_states(
	struct gegexset* set, struct gegex* ele)
{
	ENTER;
	
	dpv(ele);
	
	if (!gegexset_contains(set, ele))
	{
		gegexset_add(set, ele);
		
		unsigned i, n;
		for (i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			gegex_add_lamda_states(set,
				ele->lambda_transitions.data[i]);
		}
	}
	
	EXIT;
}
















