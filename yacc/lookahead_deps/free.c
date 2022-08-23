
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_lookahead_deps(struct lookahead_deps* this)
{
	ENTER;
	
	avl_free_tree(this->dependant_of);
	avl_free_tree(this->dependant_on);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

