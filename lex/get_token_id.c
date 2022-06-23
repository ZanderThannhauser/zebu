
#include <debug.h>

#include <avl/safe_insert.h>

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
	
	struct avl_node_t* node = avl_search(&this->nodes, &token);
	
	if (node)
	{
		TODO;
	}
	else
	{
		retval = this->next_id++;
		safe_avl_insert(&this->nodes, new_node(retval, token));
	}
	
	EXIT;
	return retval;
}

