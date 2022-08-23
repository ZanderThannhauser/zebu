
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_pair(void* ptr)
{
	struct pair* this = ptr;
	ENTER;
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

