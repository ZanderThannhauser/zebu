
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool set_is_empty(struct set* this)
{
	return !this->n;
}

