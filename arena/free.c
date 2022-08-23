
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_memory_arena(struct memory_arena* this)
{
	ENTER;
	
	if (this)
	{
		for (unsigned i = 0, n = this->mmaps.n; i < n; i++)
		{
			struct mentry* mentry = &(this->mmaps.data[i]);
			
			(this->free)(this, mentry->start, mentry->size);
		}
		
		(this->realloc)(this, this->mmaps.data, 0);
		
		(this->realloc)(this, this, 0);
	}
	
	EXIT;
}

#if 0
#include <assert.h>
#include <sys/mman.h>

#include <debug.h>

#include <defines/argv0.h>

#include "struct.h"
#include "free.h"

void free_memory_arena(struct memory_arena* this)
{
/*	size_t i, n;*/
/*	typeof(*this->mmaps.data)* mentry;*/
	ENTER;
	
	#if 0
	if (this)
	{
		for (i = 0, n = this->mmaps.n; i < n; i++)
		{
			mentry = &(this->mmaps.data[i]);
			
			if (munmap(mentry->start, mentry->size) < 0)
				fprintf(stderr, "%s: munmap(): %m\n", argv0);
		}
		
		free(this->mmaps.data);
		free(this);
	}
	#endif
	
	EXIT;
}

#endif
