
#include <debug.h>

#include "struct.h"
#include "clone.h"

struct gegexset* gegexset_clone(
	const struct gegexset* other)
{
	ENTER;
	
	TODO;
	#if 0
	struct gegexset* this = smalloc(sizeof(*this));
	
	this->data = smemdup(other->data, sizeof(*other->data) * other->n);
	this->n = other->n;
	this->cap = other->n;
	
	EXIT;
	return this;
	#endif
}

