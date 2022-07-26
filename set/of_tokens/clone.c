
#include <debug.h>

#include "struct.h"
#include "clone.h"

struct tokenset* tokenset_clone(const struct tokenset* other)
{
	ENTER;
	
	struct tokenset* this = smalloc(sizeof(*this));
	
	this->n = other->n;
	this->cap = other->n;
	
	this->data = smemdup(other->data, sizeof(*other->data) * other->n);
	
	EXIT;
	return this;
}

