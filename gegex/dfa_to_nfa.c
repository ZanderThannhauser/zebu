
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

struct gbundle gegex_dfa_to_nfa(struct gegex* start)
{
	ENTER;
	
	TODO;
	#if 0
	struct gegex* end = new_gegex();
	
	struct gegexset* done = new_gegexset();
	
	struct quack* todo = new_quack();
	
	gegexset_add(done, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		if (state->is_reduction_point)
		{
			gegex_add_lambda_transition(state, end);
			state->is_reduction_point = false;
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex* to = state->transitions.data[i]->to;
			
			if (gegexset_add(done, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex* to = state->grammar_transitions.data[i]->to;
			
			if (gegexset_add(done, to))
				quack_append(todo, to);
		}
		
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			struct gegex* to = state->lambda_transitions.data[i];
			
			if (gegexset_add(done, to))
				quack_append(todo, to);
		}
	}
	
	free_quack(todo);
	
	free_gegexset(done);
	
	EXIT;
	return (struct gbundle) {start, end};
	#endif
}









