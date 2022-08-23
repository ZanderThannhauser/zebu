
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_charset(struct charset* this)
{
	ENTER;
	
	if (this)
	{
		arena_dealloc(this->arena, this->chars);
		arena_dealloc(this->arena, this);
	}
	
	EXIT;
}

