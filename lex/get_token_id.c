
#include <debug.h>

#include <avl/free_tree.h>
#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/search.h>

#include "dfa_to_id/struct.h"
#include "dfa_to_id/new.h"

#include "struct.h"
#include "get_token_id.h"

unsigned lex_get_token_id(
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
		
		struct dfa_to_id_node* new = new_dfa_to_id_node(retval, token);
		
		safe_avl_insert(this->dfa_to_id, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}












