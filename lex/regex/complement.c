
#include <debug.h>

#include <lex/phase_counter.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "complement.h"

static void helper(struct regex* regex, struct memory_arena* scratchpad)
{
	if (regex->phase != lex_phase_counter)
	{
		regex->phase = lex_phase_counter;
		regex->is_accepting = !regex->is_accepting;
		
		size_t i, n;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; i < n; i++)
			helper(regex->transitions.data[i]->to, scratchpad);
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; i < n; i++)
			helper(regex->lambda_transitions.data[i], scratchpad);
		
		// default transition?:
		if (regex->default_transition_to)
		{
			helper(regex->default_transition_to, scratchpad);
		}
		else
		{
			struct regex* phi = new_regex(scratchpad);
			phi->is_accepting = true;
			regex_set_default_transition(regex, phi);
			regex_set_default_transition(phi, phi);
		}
	}
}

void regex_complement(struct regex* start, struct memory_arena* scratchpad)
{
	ENTER;
	
	lex_phase_counter++;
	
	helper(start, scratchpad);
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
}

