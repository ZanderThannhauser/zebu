
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool stateset_contains(struct stateset* this, struct regex* element)
{
	return !!avl_search(&this->tree, element);
}
