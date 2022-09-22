
#include <assert.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include "struct.h"
#include "add_lambda_transition.h"
#include "lambda_all_accepting_states.h"

void regex_lambda_all_accepting_states(
	struct regex* start,
	struct regex* dest,
	bool accepts)
{
	ENTER;
	
	struct ptrset* done = new_ptrset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct regex* state = quack_pop(todo);
		
		if (state->accepts)
		{
			if (state != dest)
			{
				regex_add_lambda_transition(state, dest);
			}
			
			state->accepts = accepts;
		}
		
		// normal transitions:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to && ptrset_add(done, to))
				quack_append(todo, to);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct regex* to = state->lambdas.data[i];
			
			if (ptrset_add(done, to))
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
	
	free_ptrset(done);
	
	free_quack(todo);
	
	EXIT;
}




















