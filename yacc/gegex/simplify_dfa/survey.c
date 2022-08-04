
#include <assert.h>

#include <debug.h>

#include <yacc/gegex/state/struct.h>

#include <set/of_gegexes/all.h>
#include <set/of_gegexes/add.h>

#include <yacc/phase_counter.h>

#include <macros/all.h>
#include <macros/lambda.h>

#include "are_equal.h"
#include "survey.h"

void gegex_survey(
	struct avl_tree_t* cache,
	struct gegexset* unique_states,
	struct gegex* state)
{
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		unsigned i, n;
		
		state->phase = yacc_phase_counter;
		
		for (i = 0, n = state->transitions.n; i < n; i++)
			gegex_survey(cache, unique_states, state->transitions.data[i]->to);
		
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
			gegex_survey(cache, unique_states, state->grammar_transitions.data[i]->to);
		
		// only add to unique set if not equal to all:
		if (all(unique_states, lambda(bool, (struct gegex* u), !gegex_are_equal(cache, u, state))))
		{
			gegexset_add(unique_states, state);
		}
		
		assert(!state->lambda_transitions.n);
	}
	
	EXIT;
}














