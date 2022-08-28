
#if 0
#include <debug.h>

#include <lex/state/struct.h>

#include <misc/phase_counters.h>

#include "dyntable/set.h"
#include "dynvector/set.h"

#include "lstate_to_id/lstate_to_id.h"

#include "tokenset_to_id/tokenset_to_id.h"

#include "shared.h"

#include "fill_lex_tables.h"

void fill_lex_tables(
	struct out_shared* shared,
	struct lex_state* state)
{
	ENTER;
	
	if (state->phase != lex_phase_counter)
	{
		state->phase = lex_phase_counter;
		
		unsigned lid = lstate_to_id(shared->ltoi, state);
		
		dpv(lid);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			const struct ltransition* const ele = state->transitions.data[i];
			
			unsigned slid = lstate_to_id(shared->ltoi, ele->to);
			
			fill_lex_tables(shared, ele->to);
			
			dyntable_set(shared->lexer, lid, ele->value, slid);
		}
		
		if (state->default_transition_to)
		{
			unsigned slid = lstate_to_id(shared->ltoi, state->default_transition_to);
			
			fill_lex_tables(shared, state->default_transition_to);
			
			dynvector_set(shared->defaults, lid, slid);
		}
		
		if (state->EOF_transition_to)
		{
			unsigned slid = lstate_to_id(shared->ltoi, state->EOF_transition_to);
			
			fill_lex_tables(shared, state->EOF_transition_to);
			
			dynvector_set(shared->EOFs, lid, slid);
		}
		
		if (state->accepting)
		{
			unsigned tid = tokenset_to_id(shared->ttoi, state->accepting);
			
			dpv(tid);
			
			dynvector_set(shared->accepts, lid, tid);
		}
	}
	
	EXIT;
}













#endif
