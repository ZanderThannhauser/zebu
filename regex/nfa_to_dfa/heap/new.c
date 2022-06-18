
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct heap* new_heap()
{
	ENTER;
	
	struct heap* this = smalloc(sizeof(*this));
	
	this->data = 0;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

