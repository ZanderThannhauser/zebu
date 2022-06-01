
#include <debug.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "lambda_all_accepting_states.h"

static int helper(
	struct regex_state* regex,
	struct memory_arena* arena,
	struct regex_state* dest,
	unsigned new_phase,
	bool keep_accepting)
{
	int error = 0;
	ENTER;
	
	if (regex->phase != new_phase)
	{
		size_t i, n;
		
		regex->phase = new_phase;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; !error && i < n; i++)
		{
			dpv(i);
			
			struct transition* transition = regex->transitions.data[i];
			
			error = helper(
				/* regex: */ transition->to,
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_phase: */ new_phase,
				/* keep_accepting: */ keep_accepting);
		}
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; !error && i < n; i++)
		{
			dpv(i);
			
			error = helper(
				/* regex: */ regex->lambda_transitions.data[i],
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_phase: */ new_phase,
				/* keep_accepting: */ keep_accepting);
		}
		
		// default transition?:
		if (!error && regex->default_transition_to)
		{
			TODO;
		}
		
		if (regex->is_accepting)
		{
			error = regex_state_add_lambda_transition(
				/* from:  */ regex,
				/* arena: */ arena,
				/* to:    */ dest);
			
			if (!keep_accepting)
				regex->is_accepting = false;
		}
	}
	
	EXIT;
	return error;
}

int regex_lambda_all_accepting_states(
	struct regex_state* regex,
	struct memory_arena* arena,
	struct regex_state* dest,
	bool keep_accepting)
{
	int error = 0;
	ENTER;
	
	unsigned new_phase = regex->phase + 1;
	
	dpv(new_phase);
	
	error = helper(regex, arena, dest, new_phase, keep_accepting);
	
	EXIT;
	return error;
}















