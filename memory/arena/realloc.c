
#include <string.h>

#include <debug.h>

#include "prettyprint.h"
/*#include "header.h"*/
#include "get_size.h"
#include "malloc.h"
#include "dealloc.h"
#include "realloc.h"

void* arena_realloc(
	struct memory_arena* this,
	void* old, size_t size)
{
	size_t user_size;
	
	if (!old)
		return arena_malloc(this, size);
	else if (!size)
		return arena_dealloc(this, old), NULL;
	else if (size <= (user_size = arena_get_size(old)))
		return old;
	else
	{
		void *new = arena_malloc(this, size);
		
		dpv(old);
		dpv(new);
		
		memcpy(new, old, user_size);
		
		arena_dealloc(this, old);
		
		#ifdef DEBUGGING
		arena_prettyprint(this);
		#endif
		
		return new;
	}
}























