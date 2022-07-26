
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool gegexset_is_empty(struct gegexset* this)
{
	return !this->n;
}

