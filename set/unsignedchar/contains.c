
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool unsignedcharset_contains(
	const struct unsignedcharset* this,
	unsigned char element)
{
	return !!avl_search(this->tree, &element);
}

