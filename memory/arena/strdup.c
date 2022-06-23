
#include <debug.h>

#include "malloc.h"
#include "strdup.h"

char* arena_strdup(
	struct memory_arena* arena,
	const char* string)
{
	ENTER;
	
	size_t len = strlen(string);
	
	char* new = arena_malloc(arena, len + 1);
	
	memcpy(new, string, len + 1);
	
	dpvs(new);
	
	EXIT;
	return new;
}

