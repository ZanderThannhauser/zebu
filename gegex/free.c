
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

/*#include <set/unsigned/free.h>*/

/*#include <yacc/structinfo/free.h>*/

#include "grammar/struct.h"
#include "grammar/free.h"
#include "transition/struct.h"
#include "transition/free.h"

#include "struct.h"

void free_gegex(struct gegex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct ptrset* freed = new_ptrset();
	
	ptrset_add(freed, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* t = state->transitions.data[i];
			
			if (ptrset_add(freed, t->to))
				quack_append(todo, t->to);
			
			free_gegex_transition(t);
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{	
			struct gegex* to = state->lambdas.data[i];
			
			if (ptrset_add(freed, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* t = state->grammars.data[i];
			
			if (ptrset_add(freed, t->to))
				quack_append(todo, t->to);
			
			free_gegex_grammar_transition(t);
		}
		
		free(state->transitions.data);
		
		free(state->grammars.data);
		
		free(state->lambdas.data);
		
		free(state);
	}
	
	free_ptrset(freed);
	
	free_quack(todo);
	
	EXIT;
}



















