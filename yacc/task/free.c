
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "inheritance.h"
#include "free.h"

void free_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct task* this)
{
	ENTER;
	
	if (this)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this);
		#else
		free(this);
		#endif
	}
	
	EXIT;
}

