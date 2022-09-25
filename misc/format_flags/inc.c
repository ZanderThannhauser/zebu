
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct format_flags* inc_format_flags(
	struct format_flags* this)
{
	this->refcount++;
	return this;
}

