
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "inheritance.h"
#include "free.h"

void free_task(struct task* this, struct memory_arena* arena)
{
	ENTER;
	
	if (this)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		arena_dealloc(arena, this);
	}
	
	EXIT;
}

