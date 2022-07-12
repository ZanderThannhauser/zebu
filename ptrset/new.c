
#include <debug.h>

#include "struct.h"
#include "new.h"

struct ptrset* new_ptrset(int (*cmp)(const void*, const void*))
{
	ENTER;
	struct ptrset* this = smalloc(sizeof(*this));
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

