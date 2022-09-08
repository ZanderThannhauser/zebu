
#include <debug.h>

#include "struct.h"
#include "clear.h"

void regexset_clear(struct regexset* this)
{
	ENTER;
	
	avl_free_nodes(this->tree);
	
	this->n = 0;
	
	EXIT;
}

