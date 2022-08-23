
#include <string.h>

#include <debug.h>

#include "malloc.h"
#include "calloc.h"

void* arena_calloc(
	struct memory_arena* this,
	size_t nmemb, size_t size)
{
	ENTER;
	
	size_t total = nmemb * size;
	
	dpv(total);
	
	void* ptr = arena_malloc(this, total);
	
	memset(ptr, 0, total);
	
	EXIT;
	return ptr;
}

