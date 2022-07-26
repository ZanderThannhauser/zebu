
#include <debug.h>

#include "struct.h"
#include "pop.h"

const void* regexset_pop(struct regexset* this)
{
	ENTER;
	
	TODO;
	#if 0
	assert(this->n);
	
	const void* retval = this->data[--this->n];
	
	EXIT;
	return retval;
	#endif
}

