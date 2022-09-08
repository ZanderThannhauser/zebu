
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct unsignedset* inc_unsignedset(struct unsignedset* this)
{
	if (this) this->refcount++;
	return this;
}

