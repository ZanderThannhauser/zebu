
#include <debug.h>

#include <avl/free_tree.h>
#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/search.h>

#include "node/struct.h"
#include "node/new.h"
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
	
	if ((node = avl_search(this->tokens, &token)))
	{
		struct node* found = node->item;
		
		retval = found->id;
	}
	else
	{
		retval = this->next_id++;
		
		struct node* new = new_node(retval, token);
		
		safe_avl_insert(this->tokens, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}












