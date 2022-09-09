
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_regexset(struct regexset* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		
		free(this);
	}
	
	EXIT;
}

