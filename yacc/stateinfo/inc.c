
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct stateinfo* inc_stateinfo(struct stateinfo* this)
{
	if (this) this->refcount++;
	return this;
}

