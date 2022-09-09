
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool regexset_contains(
	struct regexset* this,
	struct regex* element)
{
	return !!avl_search(this->tree, element);
}

