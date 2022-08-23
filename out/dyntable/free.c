
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_dyntable(struct dyntable* this)
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

