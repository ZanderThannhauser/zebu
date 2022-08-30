
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct unsignedcharset* inc_unsignedcharset(struct unsignedcharset* this)
{
	if (this)
	{
		this->refcount++;
	}
	
	return this;
}

