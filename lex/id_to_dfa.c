
#include <avl/search.h>

#include <debug.h>

#include <assert.h>

#include "struct.h"

#include "from_node/struct.h"

#include "id_to_dfa.h"

struct regex* lex_id_to_dfa(
	struct lex* this,
	unsigned token_id)
{
	ENTER;
	
	dpv(token_id);
	
	struct avl_node_t* node = avl_search(this->dfa_from_id, &token_id);
	
	dpv(node);
	
	assert(node);
	
	struct dfa_from_id_node* dfi = node->item;
	
	struct regex* retval = dfi->token;
	
	dpv(retval);
	
	EXIT;
	return retval;
}

