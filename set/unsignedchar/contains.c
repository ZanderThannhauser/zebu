
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool unsignedcharset_contains(
	const struct unsignedcharset* this,
	unsigned char element)
{
	assert(this);
	return !!avl_search(this->tree, &element);
}

