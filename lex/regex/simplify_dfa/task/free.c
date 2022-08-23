
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_simplify_task(struct simplify_task* this)
{
	ENTER;
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

