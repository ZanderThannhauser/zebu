
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void lstatetree_discard(struct lstatetree* this, struct lex_state* ele)
{
	if (avl_delete(this->tree, ele))
	{
		this->n--;
	}
}

