
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool gegextree_contains(struct gegextree* this, struct gegex* ele)
{
	return !!avl_search(this->tree, ele);
}

