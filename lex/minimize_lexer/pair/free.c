
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_lex_pair(void* ptr)
{
	struct lex_pair* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

