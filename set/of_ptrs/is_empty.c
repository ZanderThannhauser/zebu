
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool ptrset_is_empty(struct ptrset* this)
{
	return !this->n;
}

