
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct string* inc_string(struct string* this)
{
	if (this)
		this->refcount++;
	return this;
}

