
#ifdef WITH_ARENAS

#include <debug.h>

#include "free.h"

void stdlib_free(struct memory_arena* this, void* ptr, size_t oldsize)
{
	ENTER;
	
	free(ptr);
	
	EXIT;
}


#endif
