
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>

#include <named/regex/struct.h>

#include <string/struct.h>

#include <enums/error.h>

#include "../struct.h"

#include "fragment.h"

struct regex* scope_lookup_fragment(
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
		
		node = avl_search(layer->fragments, &(const char**){&name});
		
		if (!node)
			layer = layer->prev;
	}
	
	dpv(layer);
	
	if (!layer)
	{
		fprintf(stderr, "zebu: reference to undefined regular-expression '%s'!\n", name);
		exit(e_syntax_error);
	}
	
	struct named_regex* ntoken = node->item;
	
	EXIT;
	return ntoken->regex;
}














