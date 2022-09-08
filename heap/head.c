
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "head.h"

void* heap_head(const struct heap* this)
{
	assert(this->n);
	return this->data[0];
}

