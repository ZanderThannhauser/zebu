
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_unsignedsetset(
	struct unsignedsetset* this)
{
	if (this && !--this->refcount)
	{
		avl_free_tree(this->tree);
		free(this);
	}
}

