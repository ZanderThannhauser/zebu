
#ifdef WITH_ARENAS

#include <sys/mman.h>

#include <debug.h>

#include "resize.h"

bool mmap_resize(struct memory_arena* this, void* ptr, size_t oldsize, size_t newsize)
{
	bool successful = true;
	ENTER;
	
	dpv(oldsize);
	dpv(newsize);
	
	if (mremap(ptr, oldsize, newsize, 0) == MAP_FAILED)
	{
		successful = false;
	}
	
	dpvb(successful);
	
	EXIT;
	return successful;
}



#endif
