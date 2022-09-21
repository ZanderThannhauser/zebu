
#include <stdlib.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

/*#include <set/regex/new.h>*/
/*#include <set/regex/add.h>*/
/*#include <set/regex/free.h>*/

#include "struct.h"
#include "free.h"

void free_regex(struct regex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct ptrset* freed = new_ptrset();
	
	ptrset_add(freed, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct regex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to && ptrset_add(freed, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct regex* to = state->lambdas.data[i];
			
			if (ptrset_add(freed, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct regex* to = state->EOF_transition_to;
			
			if (ptrset_add(freed, to))
				quack_append(todo, to);
		}
	
		free(state->lambdas.data);
		
		free(state);
	}
	
	free_ptrset(freed);
	
	free_quack(todo);
	
	EXIT;
}











