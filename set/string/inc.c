
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct stringset* inc_stringset(struct stringset* this)
{
	if (this) this->refcount++;
	return this;
}

