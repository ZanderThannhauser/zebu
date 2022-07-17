
#include <debug.h>

#include "struct.h"
#include "new.h"

struct ptrset* new_ptrset()
{
	ENTER;
	struct ptrset* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

