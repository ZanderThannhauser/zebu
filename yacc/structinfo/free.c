
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_structinfo(void* ptr)
{
	struct structinfo* this = ptr;
	
	if (this && !--this->refcount)
	{
		free_string(this->name);
		
		avl_free_tree(this->tree);
		
		free(this);
	}
}

