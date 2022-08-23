
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <tree/of_gegexes/free.h>

#include "struct.h"
#include "free.h"

void free_gegex_same_as_node(void* ptr)
{
	struct gegex_same_as_node* this = ptr;
	ENTER;
	
	free_gegextree(this->set);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

