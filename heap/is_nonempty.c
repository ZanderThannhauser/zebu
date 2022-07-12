
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool is_heap_nonempty(struct heap* this)
{
	return !!this->n;
}

