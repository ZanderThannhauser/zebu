
#if 0
#include <debug.h>

#include <misc/phase_counter.h>

#include <lex/state/struct.h>
#include <lex/state/new.h>

#include <lex/struct.h>

#include "lex_state_ll/add.h"
#include "lex_state_ll/find.h"

#include "merge_into_tokenizer.h"

static void helper(
	struct lex* this,
	struct memory_arena* arena,
	struct lex_state* state)
{
	struct lex_state* copy;
	ENTER;
	
	if (state->phase != phase_counter)
	{
		state->phase = phase_counter;
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
			helper(this, arena, state->transitions.data[i]->to);
		
		if (state->default_transition_to)
			helper(this, arena, state->default_transition_to);
			
		copy = lex_state_ll_find(this->tokenizer.states, state);
		
		if (!copy)
		{
			copy = new_lex_state(arena);
			
			for (unsigned i = 0, n = state->transitions.n; i < n; i++)
			{
				struct lex_state* to1 = state->transitions.data[i]->to;
				struct lex_state* to2 = lex_state_ll_find(this->tokenizer.states, to1);
				dpv(to2);
				assert(to2);
				TODO;
			}
			
			if (state->default_transition_to)
			{
				TODO;
			}
			
			lex_state_ll_add(this->tokenizer.states, copy);
		}
	}
	
	EXIT;
}

struct lex_state* merge_into_tokenizer(
	struct lex* this,
	struct memory_arena* arena,
	struct lex_state* start)
{
	ENTER;
	
	phase_counter++;
	
	helper(this, arena, start);
	
	struct lex_state* new_start = lex_state_ll_find(this->tokenizer.states, start);
	
	TODO;
	
	EXIT;
	return new_start;
}















#endif
