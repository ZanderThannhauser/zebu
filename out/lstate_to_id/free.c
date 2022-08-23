
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_lstate_to_id(struct lstate_to_id* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this);
	#endif
	
	EXIT;
}

