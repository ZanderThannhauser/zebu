
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_yacc_stateinfo(struct yacc_stateinfo* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

