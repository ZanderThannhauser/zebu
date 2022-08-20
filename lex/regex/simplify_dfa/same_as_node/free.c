
#include <stdlib.h>

#include <debug.h>

#include <tree/of_regexes/free.h>

#include "struct.h"
#include "free.h"

void free_same_as_node(void* ptr)
{
	struct same_as_node* node = ptr;
	ENTER;
	
	free_regextree(node->set);
	
	free(node);
	
	EXIT;
}

