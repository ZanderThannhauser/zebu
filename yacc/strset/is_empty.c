
#include <debug.h>

#include "struct.h"
#include "is_empty.h"

bool strset_is_empty(struct strset* this)
{
	return !this->n;
}

