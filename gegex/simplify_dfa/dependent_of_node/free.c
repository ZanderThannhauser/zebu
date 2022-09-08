
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_gegex_dependent_of_node(void* ptr)
{
	struct gegex_dependent_of_node* this = ptr;
	ENTER;
	
	avl_free_tree(this->dependent_of);
	
	free(this);
	
	EXIT;
}
