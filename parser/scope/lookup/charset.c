
#include <avl/avl.h>

#include <debug.h>

#include "../struct.h"

#include "../named/name/struct.h"

#include "../named/charset/struct.h"

#include "charset.h"

struct charset* scope_lookup_charset(struct scope* this, const char* name)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(&this->layer->charsets, &name);
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	struct named_name* nname = node->item;
	
	dpvs(nname->value);
	
	node = avl_search(&this->charsets, &nname->value);
	
	assert(node);
	
	struct named_charset* ntoken = node->item;
	
	EXIT;
	return ntoken->charset;
}














