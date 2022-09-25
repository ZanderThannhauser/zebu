
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_format_flags(struct format_flags* this)
{
	if (this && !--this->refcount)
	{
		free(this);
	}
}

