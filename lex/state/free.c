
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/add.h>

#include <set/unsigned/free.h>

#include "struct.h"
#include "free.h"

void free_lex_state(struct ptrset* freed, struct lex_state* start)
{
	ENTER;
	
	if (start)
	{
		struct quack* todo = new_quack();
		
		if (ptrset_add(freed, start))
			quack_append(todo, start);
		
		while (quack_is_nonempty(todo))
		{
			struct lex_state* state = quack_pop(todo);
			
			free_unsignedset(state->accepts);
			
			for (unsigned i = 0, n = 256; i < n; i++)
			{
				struct lex_state* to = state->transitions[i];
				
				if (to && ptrset_add(freed, to))
					quack_append(todo, to);
			}
			
			if (state->EOF_transition_to)
			{
				struct lex_state* to = state->EOF_transition_to;
				
				if (ptrset_add(freed, to))
					quack_append(todo, to);
			}
			
			free(state);
		}
		
		free_quack(todo);
	}
	
	EXIT;
}

















