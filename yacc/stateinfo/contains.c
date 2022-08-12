
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool yacc_stateinfo_contains(
	struct yacc_stateinfo* this,
	struct gegex* state)
{
	return !!avl_search(this->tree, &state);
}

