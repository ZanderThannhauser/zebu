
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "pop.h"

const char* set_pop(struct set* this)
{
	ENTER;
	
	assert(this->n);
	
	const char* retval = this->data[this->n - 1];
	
	this->n--;
	
	EXIT;
	return retval;
}

