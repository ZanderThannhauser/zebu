
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_gegex_simplify_task(struct gegex_simplify_task* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}
