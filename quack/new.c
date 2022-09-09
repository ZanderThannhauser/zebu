
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct quack* new_quack()
{
	ENTER;
	
	struct quack* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->i = 0;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

