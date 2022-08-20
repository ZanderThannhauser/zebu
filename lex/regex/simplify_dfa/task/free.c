
#include <stdlib.h>

#include <debug.h>

#include "free.h"

void free_simplify_task(struct simplify_task* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}

