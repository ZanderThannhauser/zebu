
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool tokensetset_is_empty(struct tokensetset* this)
{
	return !this->n;
}

