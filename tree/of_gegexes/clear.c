
#include <debug.h>

#include <avl/free_nodes.h>

#include "struct.h"
#include "clear.h"

void gegextree_clear(struct gegextree* this)
{
	ENTER;
	
	avl_free_nodes(this->tree);
	
	this->n = 0;
	
	EXIT;
}

