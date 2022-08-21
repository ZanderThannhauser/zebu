
#if 0
#include <stdlib.h>

#include <avl/free_nodes.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_pragma_once(struct pragma_once* this)
{
	ENTER;
	
	avl_free_nodes(&this->tree);
	
	free(this);
	
	EXIT;
}

#endif
