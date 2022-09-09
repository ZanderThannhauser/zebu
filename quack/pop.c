
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "pop.h"

void* quack_pop(struct quack* this)
{
	ENTER;
	
	assert(this->n);
	
	void* ele = this->data[this->i++];
	
	if (this->i == this->cap)
		this->i = 0;
	
	this->n--;
	
	dpv(this->n);
	dpv(this->i);
	
	EXIT;
	return ele;
}

