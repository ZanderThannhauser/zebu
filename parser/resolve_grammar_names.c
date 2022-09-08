
#include <debug.h>

#include <debug.h>

#include <gegex/state/struct.h>

#include <named/gegex/struct.h>
#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include "scope/struct.h"
#include "scope/resolve/grammar.h"

#include "resolve_grammar_names.h"

void resolve_grammar_names(struct scope* scope)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct gegexset* queued = new_gegexset();
	
	for (struct avl_node_t* i = scope->grammar->head; i; i = i->next)
	{
		const struct named_gegex* const ele = i->item;
		
		dpvs(ele->name);
		
		if (gegexset_add(queued, ele->gegex))
			quack_append(todo, ele->gegex);
	}
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex* const to = state->transitions.data[i]->to;
			
			if (gegexset_add(queued, to))
				quack_append(todo, to);
		}
		
		// grammar_transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = state->grammar_transitions.data[i];
			
			struct string* new = scope_resolve_grammar(scope, ele->grammar);
			
			free_string(ele->grammar), ele->grammar = new;
			
			if (gegexset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
	}
	
	free_gegexset(queued);
	
	free_quack(todo);
	
	EXIT;
}


































