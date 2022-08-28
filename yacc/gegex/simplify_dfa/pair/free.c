
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex_pair(void* ptr)
{
	struct gegex_pair* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}
#endif
