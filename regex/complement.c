
#include <assert.h>
#include <stddef.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include "struct.h"
#include "new.h"
#include "dotout.h"
#include "complement.h"

void regex_complement(struct regex* start)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	struct regex* phi = NULL;
	
	while (quack_is_nonempty(todo))
	{
		struct regex* const state = quack_pop(todo);
		
		state->accepts = !state->accepts;
		
		// normal transitions:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to)
			{
				if (ptrset_add(queued, to))
					quack_append(todo, to);
			}
			else
			{
				if (!phi)
				{
					phi = new_regex();
					
					phi->accepts = true;
					
					for (unsigned i = 0, n = 256; i < n; i++)
						phi->transitions[i] = phi;
				}
				
				state->transitions[i] = phi;
			}
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
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
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
}















