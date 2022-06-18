
#include <avl/avl.h>

#include <debug.h>

#include "struct.h"
#include "insert.h"

void stateset_insert(struct stateset* this, struct regex* element)
{
	ENTER;
	
	if (avl_insert(&this->tree, element))
	{
		this->n++;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}

