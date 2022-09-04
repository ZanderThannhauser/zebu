
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_ystate_to_id(struct ystate_to_id* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free(this);
	
	EXIT;
}

