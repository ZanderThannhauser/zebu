
#include <debug.h>

#include "avl.h"
#include "insert.h"

int avl_tree_insert(struct avl_tree_t* tree, void* element)
{
	int error = 0;
	
	if (!avl_insert(tree, element))
		fprintf(stderr, "%s: malloc: %m\n", argv0),
		error = e_out_of_memory;
	
	return error;
}

