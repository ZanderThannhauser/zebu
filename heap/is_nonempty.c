
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool heap_is_nonempty(struct heap* this)
{
	return !!this->n;
}

