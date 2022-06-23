
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct charset* inc_charset(struct charset* this)
{
	if (this)
		this->refcount++;
	
	return this;
}

