
#include <debug.h>

#include <set/regex/foreach.h>

#include "struct.h"
#include "foreach_lambda_transition.h"

void regex_foreach_lambda_transition(
	struct regex* state,
	void (*runme)(struct regex* to))
{
	ENTER;
	
	regexset_foreach(state->lambda_transitions, runme);
	
	EXIT;
}

