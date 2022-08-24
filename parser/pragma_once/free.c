
#include <assert.h>
#include <stdlib.h>

#include <avl/free_tree.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_pragma_once(struct pragma_once* this)
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

