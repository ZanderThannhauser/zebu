
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct gegexset* new_gegexset()
{
	ENTER;
	
	struct gegexset* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

