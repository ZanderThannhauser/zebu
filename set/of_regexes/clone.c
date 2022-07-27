
#include <memory/smalloc.h>
#include <memory/smemdup.h>

#include <debug.h>

#include "struct.h"
#include "clone.h"

struct regexset* regexset_clone(
	const struct regexset* other)
{
	ENTER;
	
	dpv(other->n);
	
	struct regexset* this = smalloc(sizeof(*this));
	
	this->data = smemdup(other->data, sizeof(*other->data) * other->n);
	this->n = other->n;
	this->cap = other->n;
	
	dpv(this->n);
	
	EXIT;
	return this;
}

