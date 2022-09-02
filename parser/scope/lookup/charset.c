
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/charset/struct.h>

#include "../struct.h"

#include "charset.h"

struct cbundle scope_lookup_charset(
	struct scope* this,
	const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node = NULL;
	
	struct scope_layer* layer = this->layer;
	
	while (layer && !node)
	{
		dpv(layer);
		
		node = avl_search(layer->charsets, &(const char**){&name});
		
		if (!node)
			layer = layer->prev;
	}
	
	dpv(layer);
	
	if (!layer)
	{
		TODO;
		exit(1);
	}
	
	struct named_charset* ncs = node->item;
	
	EXIT;
	return (struct cbundle) {ncs->is_complement, ncs->charset};
}














