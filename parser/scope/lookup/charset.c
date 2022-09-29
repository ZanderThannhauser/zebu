
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <named/charset/struct.h>

#include <enums/error.h>

#include "../struct.h"

#include "charset.h"

charset_t scope_lookup_charset(
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
		{
			layer = layer->prev;
		}
	}
	
	dpv(layer);
	
	if (!layer)
	{
		fprintf(stderr, "zebu: reference to undefined character-set '%s'!\n", name);
		exit(e_syntax_error);
	}
	
	struct named_charset* ncs = node->item;
	
	EXIT;
	return ncs->charset;
}














