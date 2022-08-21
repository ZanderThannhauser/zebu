
#include <string.h>

#include <debug.h>

/*#include "prettyprint.h"*/
/*#include "header.h"*/
#include "get_size.h"
#include "malloc.h"
#include "dealloc.h"
#include "realloc.h"

void* arena_realloc(
	struct memory_arena* this,
	void* old, size_t size)
{
	void* retval;
	ENTER;
	
	dpv(old);
	dpv(size);
	
	size_t user_size;
	
	if (!old)
	{
		retval = arena_malloc(this, size);
	}
	else if (!size)
	{
		arena_dealloc(this, old);
		retval = NULL;
	}
	else if (size <= (user_size = arena_get_size(old)))
	{
		retval = old;
	}
	else
	{
		void *new = arena_malloc(this, size);
		
		dpv(old);
		dpv(new);
		
		memcpy(new, old, user_size);
		
		arena_dealloc(this, old);
		
		return new;
	}
	
	EXIT;
	return retval;
}























