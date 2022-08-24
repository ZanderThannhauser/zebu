
#include <debug.h>

#include <misc/phase_counters.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_lambda_transition.h"

#include "dfa_to_nfa.h"

static void helper(
	struct gegex* state,
	struct gegex* end)
{
	unsigned i, n;
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		state->phase = yacc_phase_counter;
		
		if (state->is_reduction_point)
		{
			gegex_add_lambda_transition(state, end);
			state->is_reduction_point = false;
		}
		
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			helper(state->transitions.data[i]->to, end);
		}
		
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			helper(state->grammar_transitions.data[i]->to, end);
		}
		
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			helper(state->lambda_transitions.data[i], end);
		}
	}
	
	EXIT;
}

struct gbundle gegex_dfa_to_nfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* dfa)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex* end = new_gegex(arena);
	#else
	struct gegex* end = new_gegex();
	#endif
	
	yacc_phase_counter++;
	
	helper(dfa, end);
	
	EXIT;
	return (struct gbundle) {dfa, end};
}










