
#include <stdlib.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include "struct.h"
#include "free.h"

void free_regex(struct regex* start)
{
	ENTER;
	
	if (start)
	{
		struct quack* todo = new_quack();
		
		struct regexset* freed = new_regexset();
		
		regexset_add(freed, start);
		
		quack_append(todo, start);
		
		while (quack_len(todo))
		{
			struct regex* state = quack_pop(todo);
			
			for (unsigned i = 0, n = 256; i < n; i++)
			{
				struct regex* to = state->transitions[i];
				
				if (to && regexset_add(freed, to))
					quack_append(todo, to);
			}
			
			for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
			{
				struct regex* to = state->lambda_transitions.data[i];
				
				if (regexset_add(freed, to))
					quack_append(todo, to);
			}
			
			if (state->EOF_transition_to)
			{
				struct regex* to = state->EOF_transition_to;
				
				if (regexset_add(freed, to))
					quack_append(todo, to);
			}
		
			free(state->lambda_transitions.data);
			
			free(state);
		}
		
		free_regexset(freed);
		
		free_quack(todo);
	}
	
	EXIT;
}











