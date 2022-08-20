
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>

#include "../struct.h"

/*#include <named/name/struct.h>*/

#include <named/token/struct.h>

#include "token.h"

struct regex* scope_lookup_token(struct scope* this, const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node = NULL;
	
	struct scope_layer* layer = this->layer;
	
	while (layer && !node)
	{
		dpv(layer);
		
		node = avl_search(layer->fragments, &name);
		
		if (!node)
			layer = layer->prev;
	}
	
	dpv(layer);
	
	if (!layer)
	{
		TODO;
		exit(1);
	}
	
	struct named_token* ntoken = node->item;
	
	EXIT;
	return ntoken->token;
}














