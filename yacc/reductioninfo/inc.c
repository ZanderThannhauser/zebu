
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct reductioninfo* inc_reductioninfo(struct reductioninfo* this)
{
	if (this)
		this->refcount++;
	return this;
}

