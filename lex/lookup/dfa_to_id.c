
#include <debug.h>

#include <avl/free_tree.h>
#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/search.h>

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
		
		// create a singleton tokenset
		TODO;
		
		// traverse through new machine, adding new token id to accepting
		// states
		TODO;
		
		struct dfa_to_id_node*   to = new_dfa_to_id_node(retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(retval, token);
		
		safe_avl_insert(this->dfa_to_id,   to);
		safe_avl_insert(this->dfa_from_id, from);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













