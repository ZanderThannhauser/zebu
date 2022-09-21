
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct ptrset* inc_ptrset(struct ptrset* this)
{
	if (this)
		this->refcount++;
	return this;
}

