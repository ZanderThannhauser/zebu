
#include <debug.h>

#include <misc/counters.h>

#include "state/struct.h"
#include "state/foreach_transition.h"
#include "state/foreach_lambda_transition.h"
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
		regex_foreach_transition(regex, ({
			void runme(unsigned char _, struct regex* to)
			{
				helper(to, dest, new_accepting);
			}
			runme;
		}));
		
		// lambda transitions:
		regex_foreach_lambda_transition(regex, ({
			void runme(struct regex* to)
			{
				helper(to, dest, new_accepting);
			}
			runme;
		}));
		
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











