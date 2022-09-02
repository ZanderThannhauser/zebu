
#include <assert.h>

#include <debug.h>

#include <regex/state/struct.h>
#include <regex/state/free.h>

#include <set/unsigned/add.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include "../struct.h"

#include "to_node/struct.h"
#include "to_node/new.h"

#include "from_node/new.h"

#include "add_token.h"

static void helper(struct regex* start, unsigned is_accepting, bool is_literal)
{
	struct regexset* queued = new_regexset();
	
	struct quack* todo = new_quack();
	
	regexset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct regex* state = quack_pop(todo);
		
		if (state->is_accepting)
		{
			state->is_accepting = is_accepting;
			state->is_literal = is_literal;
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct regex* to = state->transitions.data[i]->to;
			
			if (regexset_add(queued, to))
				quack_append(todo, to);
		}
		
		if (state->default_transition.to)
		{
			TODO;
			#if 0
			helper(state->default_transition.to);
			#endif
		}
		
		if (state->EOF_transition_to)
		{
			TODO;
			#if 0
			helper(state->EOF_transition_to);
			#endif
		}
	}
	
	free_regexset(queued);
	
	free_quack(todo);
}

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	bool is_literal)
{
	unsigned retval;
	ENTER;
	
	dpv(token);
	
	dpvb(is_literal);
	
	struct avl_node_t* node;
	
	if ((node = avl_search(this->dfa_to_id, &token)))
	{
		struct dfa_to_id_node* found = node->item;
		
		free_regex(token);
		
		retval = found->id;
	}
	else
	{
		helper(token, retval = this->next_id++, is_literal);
		
		struct dfa_to_id_node*   to   =   new_dfa_to_id_node(retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(retval, token);
		
		avl_insert(this->dfa_to_id,   to);
		avl_insert(this->dfa_from_id, from);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













