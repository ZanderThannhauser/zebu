
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_dependent_of_node(void* ptr)
{
	struct dependent_of_node* node = ptr;
	ENTER;
	
	avl_free_tree(node->dependent_of);
	
	free(node);
	
	EXIT;
}

