
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_regex_simplify_task(struct regex_simplify_task* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}
