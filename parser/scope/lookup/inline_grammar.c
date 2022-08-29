
#include <debug.h>

#include <avl/search.h>

#include <named/gegex/struct.h>

#include "../struct.h"

#include "inline_grammar.h"

struct gegex* scope_lookup_inline_grammar(struct scope* this, const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node = NULL;
	
	struct scope_layer* layer = this->layer;
	
	while (layer && !node)
	{
		dpv(layer);
		
		node = avl_search(layer->inline_grammar, &name);
		
		if (!node)
			layer = layer->prev;
	}
	
	dpv(layer);
	
	struct gegex* gegex = NULL;
	
	if (node)
	{
		struct named_gegex* ngbundle = node->item;
		
		gegex = ngbundle->gegex;
	}
	
	EXIT;
	return gegex;
}















