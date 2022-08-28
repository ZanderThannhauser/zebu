
#if 0
#include <stdlib.h>

#include <debug.h>

#include <tree/of_gegexes/free.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex_mapping(void* a)
{
	struct gegex_mapping* this = a;
	ENTER;
	
	free_gegextree(this->original_states);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

#endif
