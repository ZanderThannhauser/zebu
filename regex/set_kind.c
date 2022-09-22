

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include "dotout.h"
#include "struct.h"
#include "set_kind.h"

void regex_set_kind(struct regex* start, unsigned accepts, enum token_kind token_kind)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct regex* state = quack_pop(todo);
		
		if (state->accepts)
		{
			state->accepts = accepts;
			state->kind = token_kind;
		}
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* to = state->transitions[i];
			
			if (to && ptrset_add(queued, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct regex* to = state->EOF_transition_to;
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	#if DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
}

