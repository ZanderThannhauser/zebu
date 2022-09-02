
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_reductioninfo(struct reductioninfo* this)
{
	if (this && !--this->refcount)
	{
		TODO;
	}
}

