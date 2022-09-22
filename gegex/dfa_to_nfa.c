
#include <assert.h>

#include <debug.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include "struct.h"
#include "new.h"
#include "add_lambda_transition.h"
#include "dfa_to_nfa.h"

#include "transition/struct.h"

#include "grammar/struct.h"

struct gbundle gegex_dfa_to_nfa(struct gegex* start)
{
	ENTER;
	
	struct gegex* end = new_gegex();
	
	struct ptrset* done = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(done, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		if (state->accepts)
		{
			gegex_add_lambda_transition(state, end);
			state->accepts = false;
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex* to = state->transitions.data[i]->to;
			
			if (ptrset_add(done, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex* to = state->grammars.data[i]->to;
			
			if (ptrset_add(done, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct gegex* to = state->lambdas.data[i];
			
			if (ptrset_add(done, to))
				quack_append(todo, to);
		}
	}
	
	free_quack(todo);
	
	free_ptrset(done);
	
	EXIT;
	return (struct gbundle) {start, end};
}









