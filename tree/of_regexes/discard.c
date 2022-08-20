
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void regextree_discard(struct regextree* this, struct regex* ele)
{
	if (avl_delete(this->tree, ele))
	{
		this->n--;
	}
}

