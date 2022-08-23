
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <tree/of_regexes/free.h>

#include "struct.h"
#include "free.h"

void free_same_as_node(void* ptr)
{
	struct same_as_node* this = ptr;
	ENTER;
	
	free_regextree(this->set);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

