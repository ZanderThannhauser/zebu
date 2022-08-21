
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "struct.h"
#include "new.h"

struct heap* new_heap(int (*cmp)(const void*, const void*))
{
	ENTER;
	
	TODO;
	#if 0
	struct heap* this = smalloc(sizeof(*this));
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
	#endif
}

