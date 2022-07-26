
#include <debug.h>

#include "struct.h"
#include "clone.h"

struct tokensetset* tokensetset_clone(
	const struct tokensetset* other)
{
	ENTER;
	
	TODO;
	#if 0
	struct tokensetset* this = smalloc(sizeof(*this));
	
	this->data = smemdup(other->data, other->n);
	this->n = other->n;
	this->cap = other->n;
	
	EXIT;
	return this;
	#endif
}

