
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct structinfo* inc_structinfo(struct structinfo* this)
{
	if (this) this->refcount++;
	return this;
}

