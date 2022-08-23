
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_regexset(struct regexset* this)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	
	arena_dealloc(this->arena, this->data);
	arena_dealloc(this->arena, this);
	
	#else
	
	free(this->data);
	free(this);
	
	#endif
	
	EXIT;
}

