

#include <debug.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include "state/struct.h"
#include "state/new.h"

#include "dotout.h"
#include "complement.h"

void regex_complement(struct regex* start)
{
	ENTER;
	
	struct regexset* queued = new_regexset();
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	struct regex* phi = NULL;
	
	while (quack_len(todo))
	{
		struct regex* const state = quack_pop(todo);
		
		state->is_accepting = !state->is_accepting;
		
		// normal transitions:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to)
			{
				if (regexset_add(queued, to))
					quack_append(todo, to);
			}
			else
			{
				if (!phi)
				{
					phi = new_regex();
					
					phi->is_accepting = true;
					
					for (unsigned i = 0, n = 256; i < n; i++)
						phi->transitions[i] = phi;
				}
				
				state->transitions[i] = phi;
			}
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			TODO;
			#if 0
			helper(regex->lambda_transitions.data[i]);
			#endif
		}
	}
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	free_regexset(queued);
	
	free_quack(todo);
	
	EXIT;
}















