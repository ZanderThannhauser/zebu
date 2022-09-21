
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool ptrset_contains(
	const struct ptrset* this,
	const void* element)
{
	return !!avl_search(this->tree, element);
}

