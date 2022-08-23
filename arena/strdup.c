
#ifdef WITH_ARENAS

#include <string.h>

#include <debug.h>

#include "memdup.h"
#include "strdup.h"

char* arena_strdup(
	struct memory_arena* arena,
	const char* str)
{
	ENTER;
	
	dpvs(str);
	
	size_t len = strlen(str);
	
	char* retval = arena_memdup(arena, str, len + 1);
	
	EXIT;
	return retval;
}

#endif
