
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_heap(struct heap* this)
{
	ENTER;
	
	arena_dealloc(this->arena, this->data);
	arena_dealloc(this->arena, this);
	
	EXIT;
}

