
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct unsignedsetset* inc_unsignedsetset(
	struct unsignedsetset* this)
{
	if (this) this->refcount++;
	return this;
}

