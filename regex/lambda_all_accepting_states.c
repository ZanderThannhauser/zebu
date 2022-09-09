
#include <assert.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

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
	
	while (quack_len(todo))
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
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to && regexset_add(done, to))
				quack_append(todo, to);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			struct regex* to = state->lambda_transitions.data[i];
			
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




















