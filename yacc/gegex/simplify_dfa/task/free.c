
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex_simplify_task(struct gegex_simplify_task* this)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

