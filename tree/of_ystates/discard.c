
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void ystatetree_discard(struct ystatetree* this, struct yacc_state* ele)
{
	if (avl_delete(this->tree, ele))
	{
		this->n--;
	}
}

