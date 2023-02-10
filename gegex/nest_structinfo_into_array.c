
#if 0
#include <assert.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_substructinfo_array_field.h>
#include <yacc/structinfo/free.h>

#include "struct.h"
#include "transition/struct.h"
#include "nest_structinfo_into_array.h"

void gegex_nest_structinfo_into_array(
	struct gegex* start,
	struct string* nestas)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct ptrset* queued = new_ptrset();
	
	quack_append(todo, start);
	
	ptrset_add(queued, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* t = state->transitions.data[i];
			
			struct structinfo* new = new_structinfo();
			
			structinfo_add_substructinfo_array_field(new, nestas, t->structinfo);
			
			if (ptrset_add(queued, t->to))
				quack_append(todo, t->to);
			
			free_structinfo(t->structinfo), t->structinfo = new;
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			TODO;
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct gegex* to = state->lambdas.data[i];
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
	}
	
	free_quack(todo);
	
	free_ptrset(queued);
	
	EXIT;
}



















#endif
