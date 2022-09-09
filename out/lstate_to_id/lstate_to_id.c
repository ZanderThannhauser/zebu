
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "lstate_to_id.h"

unsigned lstate_to_id(
	struct lstate_to_id* this,
	struct lex_state* state)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &state);
	
	if (node)
	{
		struct lstate_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct lstate_to_id_node* new = smalloc(sizeof(*new));
		
		new->lstate = state;
		new->id = retval = this->next++;
		
		avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}
