
#include <avl/avl.h>

#include <debug.h>

#include <memory/sstrndup.h>
#include <memory/smalloc.h>
#include <memory/arena/strdup.h>
#include <memory/arena/dealloc.h>

#include <misc/phase_counter.h>

#include "scope/struct.h"
#include "scope/named/grammar/struct.h"
#include "scope/resolve/grammar.h"

#include "production/gegex/state/struct.h"

#include "resolve_grammar_names.h"

static void fix(
	struct gegex* state,
	struct scope* scope)
{
	size_t i, n;
	ENTER;
	
	if (state->phase != phase_counter)
	{
		state->phase = phase_counter;
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			const struct transition* const ele = state->transitions.data[i];
			fix(ele->to, scope);
		}
		
		// grammar_transitions:
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const ele = state->grammar_transitions.data[i];
			
			dpvs(ele->grammar);
			
			ele->start = scope_resolve_grammar(scope, &ele->grammar);
			
			dpvs(ele->grammar);
			
			dpv(ele->start);
			
			fix(ele->to, scope);
		}
		
		// lambda_transitions:
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			fix(state->lambda_transitions.data[i], scope);
		}
	}
	
	EXIT;
}

void resolve_grammar_names(struct scope* scope)
{
	ENTER;
	
	phase_counter++;
	
	for (struct avl_node_t* i = scope->grammar.head; i; i = i->next)
	{
		const struct named_grammar* const ele = i->item;
		
		dpvs(ele->name);
		
		fix(ele->start, scope);
	}
	
	EXIT;
}










