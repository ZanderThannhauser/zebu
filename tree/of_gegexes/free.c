
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegextree(struct gegextree* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

