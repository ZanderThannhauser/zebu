
#include <assert.h>

#include <debug.h>

#include <avl/free_tree.h>
#include <avl/search.h>
#include <avl/insert.h>

#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>

#include <misc/phase_counters.h>

#include <set/of_tokens/add.h>

#include "../struct.h"

#include "to_node/struct.h"
#include "to_node/new.h"

#include "from_node/new.h"

#include "add_token.h"

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
		retval = this->next_id++;
		
		void helper(struct regex* state)
		{
			unsigned i, n;
			ENTER;
			
			if (state->phase != lex_phase_counter)
			{
				state->phase = lex_phase_counter;
				
				assert(!state->lambda_transitions.n);
				
				if (state->is_accepting)
					state->is_accepting = retval;
				
				for (i = 0, n = state->transitions.n; i < n; i++)
					helper(state->transitions.data[i]->to);
				
				if (state->default_transition_to)
					helper(state->default_transition_to);
					
				if (state->EOF_transition_to)
					helper(state->EOF_transition_to);
			}
			
			EXIT;
		}
		
		lex_phase_counter++, helper(token);
		
		#ifdef WITH_ARENAS
		struct dfa_to_id_node*   to = new_dfa_to_id_node(this->arena, retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(this->arena, retval, token);
		#else
		struct dfa_to_id_node*   to = new_dfa_to_id_node(retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(retval, token);
		#endif
		
		avl_insert(this->dfa_to_id,   to);
		avl_insert(this->dfa_from_id, from);
		
		if (is_literal)
			tokenset_add(this->disambiguations.literal_ids, retval);
		else
			tokenset_add(this->disambiguations.regex_ids, retval);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













