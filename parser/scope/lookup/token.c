
#include <avl/search.h>

#include <debug.h>

#include "../struct.h"

#include "../named/name/struct.h"

#include "../named/token/struct.h"

#include "token.h"

struct regex* scope_lookup_token(struct scope* this, const char* name)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->layer->tokens, &name);
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	struct named_name* nname = node->item;
	
	dpvs(nname->value);
	
	node = avl_search(this->tokens, &nname->value);
	
	assert(node);
	
	struct named_token* ntoken = node->item;
	
	EXIT;
	return ntoken->token;
}














