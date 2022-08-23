
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void gegextree_discard(struct gegextree* this, struct gegex* ele)
{
	if (avl_delete(this->tree, ele))
	{
		this->n--;
	}
}

