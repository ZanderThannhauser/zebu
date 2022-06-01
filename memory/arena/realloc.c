
#include <string.h>

#include <debug.h>

#include "prettyprint.h"
/*#include "header.h"*/
#include "get_size.h"
#include "malloc.h"
#include "dealloc.h"
#include "realloc.h"

int arena_realloc(
	struct memory_arena* this,
	void** ptr, size_t size)
{
	int error = 0;
	size_t user_size;
	ENTER;
	
	dpv(*ptr);
	dpv(size);
	
	if (!*ptr)
		error = arena_malloc(this, ptr, size);
	else if (!size)
		arena_dealloc(this, *ptr);
	else if (size > (user_size = arena_get_size(*ptr)))
	{
		void *old = *ptr, *new = NULL;
		
		dpv(old);
		
		error = arena_malloc(this, &new, size);
		
		if (!error)
		{
			dpv(new);
			
			memcpy(new, old, user_size);
			
			arena_dealloc(this, old);
			
			*ptr = new;
			
			#ifdef DEBUGGING
			arena_prettyprint(this);
			#endif
		}
	}
	
	EXIT;
	return error;
}























