
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <set/lexstate/add.h>

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
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* to = state->transitions[i];
			
			if (to && lexstateset_add(freed, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			if (lexstateset_add(freed, to))
				quack_append(todo, to);
		}
		
		free(state);
	}
	
	free_quack(todo);
	
	EXIT;
}

















