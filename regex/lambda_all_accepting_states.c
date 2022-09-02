
#include <debug.h>

#include <quack/struct.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include "state/struct.h"
#include "state/add_lambda_transition.h"

#include "lambda_all_accepting_states.h"

void regex_lambda_all_accepting_states(
	struct regex* start,
	struct regex* dest,
	bool new_accepting)
{
	ENTER;
	
	struct regexset* done = new_regexset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	while (todo->n)
	{
		struct regex* state = quack_pop(todo);
		
		if (state->is_accepting)
		{
			if (state != dest)
			{
				regex_add_lambda_transition(state, dest);
			}
			
			state->is_accepting = new_accepting;
		}
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct regex* to = state->transitions.data[i]->to;
			
			if (regexset_add(done, to))
				quack_append(todo, to);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			struct regex* to = state->lambda_transitions.data[i];
			
			if (regexset_add(done, to))
				quack_append(todo, to);
			
		}
		
		if (state->default_transition.to)
		{
			struct regex* to = state->default_transition.to;
			
			if (regexset_add(done, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			TODO;
			#if 0
			helper(regex->EOF_transition_to, dest, new_accepting);
			#endif
		}
	}
	
	free_regexset(done);
	
	free_quack(todo);
	
	EXIT;
}




















