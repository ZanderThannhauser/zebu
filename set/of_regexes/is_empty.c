
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool regexset_is_empty(struct regexset* this)
{
	return !this->n;
}

