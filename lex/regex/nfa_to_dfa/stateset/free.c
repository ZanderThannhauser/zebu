
#include <avl/free_nodes.h>
#include <avl/avl.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_stateset(struct stateset* this)
{
	ENTER;
	
	dpv(this);
	
	avl_free_nodes(&this->tree);
	
	free(this);
	
	EXIT;
}

