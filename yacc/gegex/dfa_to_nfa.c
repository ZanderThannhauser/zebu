
#if 0
#include <debug.h>

#include <misc/phase_counters.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_lambda_transition.h"

#include "dfa_to_nfa.h"

static void helper(
	struct gegex* state,
	struct memory_arena* scratchpad,
	struct gegex* end)
{
	unsigned i, n;
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		state->phase = yacc_phase_counter;
		
		if (state->is_reduction_point)
		{
			gegex_add_lambda_transition(state, scratchpad, end);
			state->is_reduction_point = false;
		}
		
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			helper(state->transitions.data[i]->to, scratchpad, end);
		}
		
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			helper(state->grammar_transitions.data[i]->to, scratchpad, end);
		}
		
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			helper(state->lambda_transitions.data[i], scratchpad, end);
		}
	}
	
	EXIT;
}

struct gbundle gegex_dfa_to_nfa(
	struct gegex* dfa,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct gegex* end = new_gegex(scratchpad);
	
	yacc_phase_counter++;
	
	helper(dfa, scratchpad, end);
	
	EXIT;
	return (struct gbundle) {dfa, end};
}










#endif
