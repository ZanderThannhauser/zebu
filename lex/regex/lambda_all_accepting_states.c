

#include <debug.h>

#include <lex/phase_counter.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "lambda_all_accepting_states.h"

static void helper(
	struct regex* regex,
	struct memory_arena* arena,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	if (regex->phase != lex_phase_counter)
	{
		size_t i, n;
		
		regex->phase = lex_phase_counter;
		
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
			helper(
				/* regex: */ regex->default_transition_to,
				/* arena: */ arena,
				/* dest:  */ dest,
				/* new_accepting: */ new_accepting);
		}
		
		if (regex->is_accepting)
		{
			if (regex != dest)
			{
				regex_add_lambda_transition(
					/* from:  */ regex,
					/* arena: */ arena,
					/* to:    */ dest);
			}
			
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
	
	lex_phase_counter++;
	
	dpv(lex_phase_counter);
	
	helper(regex, arena, dest, new_accepting);
	
	EXIT;
}













