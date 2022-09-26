
#include <debug.h>

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

#include <gegex/grammar/struct.h>
#include <gegex/transition/struct.h>
#include <gegex/struct.h>

#include <named/gegex/struct.h>

#include <yacc/structinfo/resolve_grammar_names.h>

/*#include <set/gegex/new.h>*/
/*#include <set/gegex/add.h>*/
/*#include <set/gegex/free.h>*/

#include "scope/struct.h"
#include "scope/resolve/grammar.h"

#include "resolve_grammar_names.h"

void resolve_grammar_names(struct scope* scope)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct ptrset* queued = new_ptrset();
	
	for (struct avl_node_t* i = scope->grammar->head; i; i = i->next)
	{
		const struct named_gegex* const ele = i->item;
		
		dpvs(ele->name);
		
		if (ptrset_add(queued, ele->gegex))
			quack_append(todo, ele->gegex);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex* const to = state->transitions.data[i]->to;
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
		
		// grammar_transitions:
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = state->grammars.data[i];
			
			dpvs(ele->grammar);
			
			struct string* new = scope_resolve_grammar(scope, ele->grammar);
			
			dpvs(new);
			
			free_string(ele->grammar), ele->grammar = new;
			
			structinfo_resolve_grammar_names(ele->structinfo, new);
			
			if (ptrset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
}


































