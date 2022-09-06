

#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "complement.h"

void regex_complement(struct regex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct regex* const state = quack_pop(todo);
		
		TODO;
		#if 0
		regex->is_accepting = !regex->is_accepting;
		
		// normal transitions:
		for (i = 0, n = regex->transitions.n; i < n; i++)
		{
			#ifdef WITH_ARENAS
			helper(arena, regex->transitions.data[i]->to);
			#else
			helper(regex->transitions.data[i]->to);
			#endif
		}
		
		// lambda transitions:
		for (i = 0, n = regex->lambda_transitions.n; i < n; i++)
		{
			#ifdef WITH_ARENAS
			helper(arena, regex->lambda_transitions.data[i]);
			#else
			helper(regex->lambda_transitions.data[i]);
			#endif
		}
		
		// default transition?:
		if (regex->default_transition_to)
		{
			#ifdef WITH_ARENAS
			helper(arena, regex->default_transition_to);
			#else
			helper(regex->default_transition_to);
			#endif
		}
		else
		{
			#ifdef WITH_ARENAS
			struct regex* phi = new_regex(arena);
			#else
			struct regex* phi = new_regex();
			#endif
			
			phi->is_accepting = true;
			
			regex_set_default_transition(regex, phi);
			regex_set_default_transition(phi, phi);
		}
		#endif
	}
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	free_quack(todo);
	
	EXIT;
}















