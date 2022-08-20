
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool regextree_contains(struct regextree* this, struct regex* ele)
{
	return !!avl_search(this->tree, ele);
}

