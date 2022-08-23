
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegexset(struct gegexset* this)
{
	ENTER;
	
	arena_dealloc(this->arena, this->data);
	arena_dealloc(this->arena, this);
	
	EXIT;
}

