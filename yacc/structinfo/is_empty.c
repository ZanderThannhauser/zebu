
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "is_empty.h"

bool structinfo_is_empty(
	const struct structinfo* this)
{
	return !this->tree->head;
}

