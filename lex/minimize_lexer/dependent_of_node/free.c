
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_lex_dependent_of_node(void* ptr)
{
	struct lex_dependent_of_node* this = ptr;
	ENTER;
	
	avl_free_tree(this->dependent_of);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

