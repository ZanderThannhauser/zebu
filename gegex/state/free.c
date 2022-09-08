
#include <debug.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"

void free_gegex(struct gegex* start)
{
	ENTER;
	
	if (start)
	{
		struct quack* todo = new_quack();
		
		struct gegexset* freed = new_gegexset();
		
		gegexset_add(freed, start);
		quack_append(todo, start);
		
		while (quack_len(todo))
		{
			struct gegex* state = quack_pop(todo);
			
			for (unsigned i = 0, n = state->transitions.n; i < n; i++)
			{
				struct gegex_transition* t = state->transitions.data[i];
				
				if (gegexset_add(freed, t->to))
					quack_append(todo, t->to);
				
				free_structinfo(t->structinfo);
				
				free(t);
			}
			
			for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
			{
				struct gegex_grammar_transition* t = state->grammar_transitions.data[i];
				
				if (gegexset_add(freed, t->to))
				{
					quack_append(todo, t->to);
				}
				
				free_string(t->grammar);
				
				free_structinfo(t->structinfo);
				
				free(t);
			}
			
			for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
			{
				struct gegex* to = state->lambda_transitions.data[i];
				
				if (gegexset_add(freed, to))
				{
					quack_append(todo, to);
				}
			}
			
			free(state->transitions.data);
			
			free(state->grammar_transitions.data);
			
			free(state->lambda_transitions.data);
			
			free(state);
		}
		
		free_gegexset(freed);
		
		free_quack(todo);
	}
	
	EXIT;
}



















