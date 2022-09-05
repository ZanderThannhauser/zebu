
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool stringset_is_empty(
	const struct stringset* this)
{
	return !this->tree->head;
}

