
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_structinfo(void* ptr)
{
	struct structinfo* this = ptr;
	
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		
		free(this);
	}
}

