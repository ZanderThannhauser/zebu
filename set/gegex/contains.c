
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool gegexset_contains(
	const struct gegexset* this,
	struct gegex* element)
{
	return !!avl_search(this->tree, element);
}

