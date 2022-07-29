
#include <debug.h>

#include <lex/phase_counter.h>

#include "state/struct.h"

#include "dotout.h"
#include "complement.h"

static void helper(struct regex* regex)
{
	if (regex->phase != lex_phase_counter)
	{
		regex->phase = lex_phase_counter;
		regex->is_accepting = !regex->is_accepting;
		
		size_t i, n;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; i < n; i++)
			helper(regex->transitions.data[i]->to);
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; i < n; i++)
			helper(regex->lambda_transitions.data[i]);
		
		// default transition?:
		if (regex->default_transition_to)
			helper(regex->default_transition_to);
	}
}

void regex_complement(struct regex* start)
{
	ENTER;
	
	lex_phase_counter++;
	
	helper(start);
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
}

