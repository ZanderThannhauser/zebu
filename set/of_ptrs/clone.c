
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "clone.h"

struct ptrset* ptrset_clone(
	const struct ptrset* other)
{
	ENTER;
	
	TODO;
	#if 0
	struct ptrset* this = smalloc(sizeof(*this));
	
	this->data = smemdup(other->data, other->n);
	this->n = other->n;
	this->cap = other->n;
	
	EXIT;
	return this;
	#endif
}

