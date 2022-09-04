
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <set/lexstate/add.h>

#include <set/unsignedchar/free.h>

#include "struct.h"
#include "free.h"

void free_lex_state(struct lexstateset* freed, struct lex_state* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	if (lexstateset_add(freed, start))
		quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct lex_state* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct lex_transition* trans = state->transitions.data[i];
			
			if (lexstateset_add(freed, trans->to))
				quack_append(todo, trans->to);
			
			free(trans);
		}
		
		if (state->default_transition.to)
		{
			free_unsignedcharset(state->default_transition.exceptions);
			
			if (lexstateset_add(freed, state->default_transition.to))
				quack_append(todo, state->default_transition.to);
		}
		
		if (state->EOF_transition_to)
		{
			if (lexstateset_add(freed, state->EOF_transition_to))
				quack_append(todo, state->EOF_transition_to);
		}
		
		free(state->transitions.data);
		
		free(state);
	}
	
	free_quack(todo);
	
	EXIT;
}

















