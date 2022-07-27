
#include <stdlib.h>

#include <debug.h>

#include "free.h"

void free_iterator(struct iterator* this)
{
	ENTER;
	free(this);
	EXIT;
}

