
#include <debug.h>

#include <lex/regex/state/struct.h>

#include <set/of_regexes/contains.h>
#include <set/of_regexes/add.h>

#include "add_lamda_states.h"

void regex_add_lamda_states(
	struct regexset* set, struct regex* ele)
{
	ENTER;
	
	dpv(ele);
	
	if (!regexset_contains(set, ele))
	{
		regexset_add(set, ele);
		
		unsigned i, n;
		for (i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			regex_add_lamda_states(set,
				ele->lambda_transitions.data[i]);
		}
	}
	
	EXIT;
}
















