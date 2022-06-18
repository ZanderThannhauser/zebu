

#include <debug.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "phase_counter.h"
#include "lambda_all_accepting_states.h"

static void helper(
	struct regex* regex,
	struct memory_arena* arena,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	if (regex->phase != phase_counter)
	{
		size_t i, n;
		
		regex->phase = phase_counter;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; i < n; i++)
		{
			helper(
				/* regex: */ regex->transitions.data[i]->to,
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_accepting: */ new_accepting);
		}
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; i < n; i++)
		{
			helper(
				/* regex: */ regex->lambda_transitions.data[i],
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_accepting: */ new_accepting);
		}
		
		// default transition?:
		if (regex->default_transition_to)
		{
			TODO;
		}
		
		if (regex->is_accepting)
		{
			regex_add_lambda_transition(
				/* from:  */ regex,
				/* arena: */ arena,
				/* to:    */ dest);
			
			regex->is_accepting = new_accepting;
		}
	}
	
	EXIT;
}

void regex_lambda_all_accepting_states(
	struct regex* regex,
	struct memory_arena* arena,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	phase_counter++;
	
	dpv(phase_counter);
	
	helper(regex, arena, dest, new_accepting);
	
	EXIT;
}













