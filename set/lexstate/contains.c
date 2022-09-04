
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool lexstateset_contains(
	const struct lexstateset* this,
	struct lex_state* element)
{
	return !!avl_search(this->tree, element);
}

