
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct regexset* inc_regexset(struct regexset* this)
{
	if (this) this->refcount++;
	return this;
}

