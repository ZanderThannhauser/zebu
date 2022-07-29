
#include <debug.h>

#include <yacc/state/struct.h>

#include <yacc/phase_counter.h>

#include "dyntable/set.h"

#include "dynvector/set.h"

#include "ystate_to_id/ystate_to_id.h"

#include "lstate_to_id/lstate_to_id.h"

#include "tokenset_to_id/tokenset_to_id.h"

#include "tokenset_to_id/grammar_to_id.h"

#include "shared.h"
#include "fill_lex_tables.h"
#include "fill_yacc_tables.h"

void fill_yacc_tables(
	struct out_shared* shared,
	struct yacc_state* ystate)
{
	ENTER;
	
	if (ystate->phase != yacc_phase_counter)
	{
		ystate->phase = yacc_phase_counter;
		
		unsigned yid = ystate_to_id(shared->ytoi, ystate);
		
		dpv(yid);
		
		// tokenizer:
		{
			unsigned lid = lstate_to_id(shared->ltoi, ystate->tokenizer_start);
			
			fill_lex_tables(shared, ystate->tokenizer_start);
			
			dynvector_set(shared->starts, yid, lid);
		}
		
		// shift transitions:
		for (unsigned i = 0, n = ystate->transitions.n; i < n; i++)
		{
			struct ytransition* const ele = ystate->transitions.data[i];
			
			unsigned tid = tokenset_to_id(shared->ttoi, ele->value);
			
			unsigned syid = ystate_to_id(shared->ytoi, ele->to);
			
			fill_yacc_tables(shared, ele->to);
			
			dyntable_set(shared->shifts, yid, tid, syid);
		}
		
		// reduce transitions:
		for (unsigned i = 0, n = ystate->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* const ele = ystate->reduction_transitions.data[i];
			
			unsigned tid = tokenset_to_id(shared->ttoi, ele->value);
			
			unsigned gid = grammar_to_id(shared->ttoi, ele->reduce_as);
			
			dyntable_set(shared->reduces, yid, tid, gid);
		}
		
		// grammar transitions:
		for (unsigned i = 0, n = ystate->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* const ele = ystate->grammar_transitions.data[i];
			
			unsigned gid = grammar_to_id(shared->ttoi, ele->grammar);
			
			unsigned syid = ystate_to_id(shared->ytoi, ele->to);
			
			fill_yacc_tables(shared, ele->to);
			
			dyntable_set(shared->shifts, yid, gid, syid);
		}
	}
	
	EXIT;
}

















