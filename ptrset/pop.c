
#include <debug.h>

#include "struct.h"
#include "pop.h"

const void* ptrset_pop(struct ptrset* this)
{
	ENTER;
	
	assert(this->n);
	
	const void* retval = this->data[--this->n];
	
	EXIT;
	return retval;
}

