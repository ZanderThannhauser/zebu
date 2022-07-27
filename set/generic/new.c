
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct set* new_set(int (*cmp)(const void*, const void*))
{
	ENTER;
	struct set* this = smalloc(sizeof(*this));
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

