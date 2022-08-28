
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <tree/of_lstates/free.h>

#include "struct.h"
#include "free.h"

void free_lex_same_as_node(void* ptr)
{
	struct lex_same_as_node* this = ptr;
	ENTER;
	
	free_lstatetree(this->set);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}
#endif
