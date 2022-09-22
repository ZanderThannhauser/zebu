
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <lex/state/free.h>

#include <set/unsigned/free.h>

#include <yacc/reductioninfo/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_yacc_state(struct yacc_state* start)
{
	ENTER;
	
	struct ptrset* yacc_queued = new_ptrset();
	
	struct ptrset* lex_queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(yacc_queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct yacc_state* state = quack_pop(todo);
		
		free_lex_state(lex_queued, state->tokenizer_start);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state_transition* const ele = state->transitions.data[i];
			
			free_unsignedset(ele->on);
			
			if (ptrset_add(yacc_queued, ele->to))
				quack_append(todo, ele->to);
			
			free(ele);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state_grammar_transition* const ele = state->grammar_transitions.data[i];
			
			free_string(ele->grammar);
			
			if (ptrset_add(yacc_queued, ele->to))
				quack_append(todo, ele->to);
			
			free(ele);
		}
		
		for (unsigned i = 0, n = state->reduce_transitions.n; i < n; i++)
		{
			struct yacc_state_reduce_transition* const ele = state->reduce_transitions.data[i];
			
			free_unsignedset(ele->on);
			
			free_string(ele->reduce_as);
			
			free_string(ele->grammar);
			
			free_reductioninfo(ele->reductioninfo);
			
			free_structinfo(ele->structinfo);
			
			free(ele);
		}
		
		free(state->transitions.data);
		
		free(state->grammar_transitions.data);
		
		free(state->reduce_transitions.data);
		
		free(state);
	}
	
	free_ptrset(yacc_queued);
	
	free_ptrset(lex_queued);
	
	free_quack(todo);
	
	EXIT;
}

















