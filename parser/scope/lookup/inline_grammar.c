
#include <debug.h>

#include <avl/search.h>

#include <named/gbundle/struct.h>

#include "../struct.h"

#include "inline_grammar.h"

struct gbundle scope_lookup_inline_grammar(
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
		
		node = avl_search(layer->inline_grammar, &name);
		
		if (!node)
			layer = layer->prev;
	}
	
	dpv(layer);
	
	struct gegex* start = NULL;
	struct gegex* end = NULL;
	
	if (layer)
	{
		struct named_gbundle* ngbundle = node->item;
		
		start = ngbundle->start;
		end = ngbundle->end;
	}
	
	EXIT;
	return (struct gbundle) {start, end};
}
















