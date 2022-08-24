
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool lstatetree_contains(struct lstatetree* this, struct lex_state* ele)
{
	return !!avl_search(this->tree, ele);
}

