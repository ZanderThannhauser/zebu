
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct stringset* inc_stringset(struct stringset* this)
{
	this->refcount++;
	return this;
}

