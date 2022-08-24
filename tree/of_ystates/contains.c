
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool ystatetree_contains(struct ystatetree* this, struct yacc_state* ele)
{
	return !!avl_search(this->tree, ele);
}

