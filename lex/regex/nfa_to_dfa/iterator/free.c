
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_iterator(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct iterator* this
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

