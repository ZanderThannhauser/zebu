
#include <debug.h>

#include <misc/counters.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "lambda_all_accepting_states.h"

static void helper(
	struct regex* regex,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	if (regex->phase != phase_counter)
	{
		size_t i, n;
		
		regex->phase = phase_counter;
		
		if (regex->is_accepting)
		{
			if (regex != dest)
			{
				regex_add_lambda_transition(regex, dest);
			}
			
			regex->is_accepting = new_accepting;
		}
		
		// normal transitions:
		for (unsigned i = 0, n = regex->transitions.n; i < n; i++)
		{
			struct regex_transition* ele = regex->transitions.data[i];
			helper(ele->to, dest, new_accepting);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = regex->lambda_transitions.n; i < n; i++)
		{
			helper(regex->lambda_transitions.data[i], dest, new_accepting);
		}
		
		if (regex->default_transition_to)
		{
			helper(regex->default_transition_to, dest, new_accepting);
		}
		
		if (regex->EOF_transition_to)
		{
			helper(regex->EOF_transition_to, dest, new_accepting);
		}
	}
	
	EXIT;
}

void regex_lambda_all_accepting_states(
	struct regex* regex,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	phase_counter++;
	
	dpv(phase_counter);
	
	helper(regex, dest, new_accepting);
	
	EXIT;
}











