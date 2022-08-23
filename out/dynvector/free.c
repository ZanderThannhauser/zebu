
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_dynvector(struct dynvector* this)
{
	ENTER;
	
	avl_free_tree(this->list);
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this);
	#endif
	
	EXIT;
}

