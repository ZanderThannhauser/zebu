
#ifdef VERBOSE

#include <debug.h>

#include "struct.h"
#include "len.h"

unsigned heap_len(const struct heap* this)
{
	return this->n;
}

#endif
