
#include <debug.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "phase_counter.h"
#include "lambda_all_accepting_states.h"

static int helper(
	struct regex_state* regex,
	struct memory_arena* arena,
	struct regex_state* dest,
	bool new_accepting)
{
	int error = 0;
	ENTER;
	
	if (regex->phase != phase_counter)
	{
		size_t i, n;
		
		regex->phase = phase_counter;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; !error && i < n; i++)
		{
			dpv(i);
			
			struct transition* transition = regex->transitions.data[i];
			
			error = helper(
				/* regex: */ transition->to,
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_accepting: */ new_accepting);
		}
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; !error && i < n; i++)
		{
			dpv(i);
			
			error = helper(
				/* regex: */ regex->lambda_transitions.data[i],
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_accepting: */ new_accepting);
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
			
			regex->is_accepting = new_accepting;
		}
	}
	
	EXIT;
	return error;
}

int regex_lambda_all_accepting_states(
	struct regex_state* regex,
	struct memory_arena* arena,
	struct regex_state* dest,
	bool new_accepting)
{
	int error = 0;
	ENTER;
	
	phase_counter++;
	
	dpv(phase_counter);
	
	error = helper(regex, arena, dest, new_accepting);
	
	EXIT;
	return error;
}















