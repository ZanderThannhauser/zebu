
#include <debug.h>

#include <avl/free_tree.h>
#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/search.h>

#include <lex/regex/state/struct.h>

#include <misc/phase_counter.h>

#include "../struct.h"

#include "to_node/struct.h"
#include "to_node/new.h"
#include "from_node/new.h"

#include "dfa_to_id.h"

unsigned lex_dfa_to_id(
	struct lex* this,
	struct regex* token)
{
	unsigned retval;
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node;
	
	if ((node = avl_search(this->dfa_to_id, &token)))
	{
		struct dfa_to_id_node* found = node->item;
		
		retval = found->id;
	}
	else
	{
		retval = this->next_id++;
		
		void helper(struct regex* state)
		{
			unsigned i, n;
			ENTER;
			
			if (state->phase != phase_counter)
			{
				state->phase = phase_counter;
				
				assert(!state->lambda_transitions.n);
				
				if (state->is_accepting)
					state->is_accepting = retval;
				
				for (i = 0, n = state->transitions.n; i < n; i++)
					helper(state->transitions.data[i]->to);
				
				if (state->default_transition_to)
					helper(state->default_transition_to);
			}
			
			EXIT;
		}
		
		phase_counter++, helper(token);
		
		struct dfa_to_id_node*   to = new_dfa_to_id_node(retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(retval, token);
		
		safe_avl_insert(this->dfa_to_id,   to);
		safe_avl_insert(this->dfa_from_id, from);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













