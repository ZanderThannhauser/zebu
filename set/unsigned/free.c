
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_unsignedset(void* ptr)
{
	struct unsignedset* const this = ptr;
	
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		free(this);
	}
}

