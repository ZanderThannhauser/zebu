
#include <stdlib.h>

#include <debug.h>

#include <set/unsignedchar/free.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
/*#include <set/regex/foreach.h>*/
#include <set/regex/free.h>

#include <quack/struct.h>

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
		
		while (todo->n)
		{
			struct regex* state = quack_pop(todo);
			
			for (unsigned i = 0, n = state->transitions.n; i < n; i++)
			{
				struct regex_transition* t = state->transitions.data[i];
				
				if (regexset_add(freed, t->to))
				{
					quack_append(todo, t->to);
				}
				
				free(t);
			}
			
			for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
			{
				struct regex* to = state->lambda_transitions.data[i];
				
				if (regexset_add(freed, to))
				{
					quack_append(todo, to);
				}
			}
			
			if (state->default_transition.to)
			{
				struct regex* to = state->default_transition.to;
				
				if (regexset_add(freed, to))
				{
					quack_append(todo, to);
				}
				
				free_unsignedcharset(state->default_transition.exceptions);
			}
			
			if (state->EOF_transition_to)
			{
				struct regex* to = state->EOF_transition_to;
				
				if (regexset_add(freed, to))
				{
					quack_append(todo, to);
				}
			}
		
			free(state->transitions.data);
			
			free(state->lambda_transitions.data);
			
			free(state);
		}
		
		free_regexset(freed);
		
		free_quack(todo);
	}
	
	EXIT;
}











