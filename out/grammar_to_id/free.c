
#if 0
#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_grammar_to_id(struct grammar_to_id* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free(this);
	
	EXIT;
}

#endif
