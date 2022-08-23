
#include <debug.h>

#include "../get_size.h"

#include "resize.h"

bool child_resize(struct memory_arena* arena, void* ptr, size_t oldsize, size_t newsize)
{
	ENTER;
	
	dpv(oldsize);
	dpv(newsize);
	
	// something could definately be done here
	
	// something about looking at the next block, and if it's free and if
		// the combined size would fit `newsize`, then merge?
	
	EXIT;
	return false;
}

