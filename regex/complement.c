

#include <debug.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include <set/unsignedchar/new.h>
#include <set/unsignedchar/add.h>
#include <set/unsignedchar/free.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "complement.h"

void regex_complement(struct regex* start)
{
	ENTER;
	
	struct regexset* queued = new_regexset();
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct regex* const state = quack_pop(todo);
		
		state->is_accepting = !state->is_accepting;
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct regex* const to = state->transitions.data[i]->to;
			
			if (regexset_add(queued, to))
				quack_append(todo, to);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			TODO;
			#if 0
			helper(regex->lambda_transitions.data[i]);
			#endif
		}
		
		// default transition?:
		if (state->default_transition.to)
		{
			TODO;
			#if 0
			helper(regex->default_transition_to);
			#endif
		}
		else
		{
			struct regex* phi = new_regex();
			
			phi->is_accepting = true;
			
			struct unsignedcharset* exceptions = new_unsignedcharset();
			
			for (unsigned i = 0, n = state->transitions.n; i < n; i++)
				unsignedcharset_add(exceptions, state->transitions.data[i]->value);
			
			regex_set_default_transition(state, exceptions, phi);
			
			regex_set_default_transition(phi, exceptions, phi);
			
			free_unsignedcharset(exceptions);
		}
	}
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	free_regexset(queued);
	
	free_quack(todo);
	
	EXIT;
}















