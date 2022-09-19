
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct heap* new_heap(
	int (*cmp)(const void*, const void*))
{
	ENTER;
	
	struct heap* this = malloc(sizeof(*this));
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

