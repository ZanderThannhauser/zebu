
#include <debug.h>

#include <misc/phase_counters.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "dotout.h"
#include "complement.h"

static void helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* regex)
{
	ENTER;
	
	if (regex->phase != lex_phase_counter)
	{
		regex->phase = lex_phase_counter;
		regex->is_accepting = !regex->is_accepting;
		
		size_t i, n;
		
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
	}
	
	EXIT;
}

void regex_complement(
	#ifdef WTIH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* start)
{
	ENTER;
	
	lex_phase_counter++;
	
	#ifdef WITH_ARENAS
	helper(arena, start);
	#else
	helper(start);
	#endif
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
}















