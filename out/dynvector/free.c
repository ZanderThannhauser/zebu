
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_dynvector(struct dynvector* this)
{
	ENTER;
	
	TODO;
	#if 0
	avl_free_tree(this->list);
	free(this);
	#endif
	
	EXIT;
}

