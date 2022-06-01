
#include <debug.h>

#include "avl.h"
#include "new.h"

int new_avl_tree(
	struct avl_tree_t** out,
	int (*compare)(const void *, const void *),
	void (*freeitem)(void *))
{
	int error = 0;
	ENTER;
	
	if (!(*out = avl_alloc_tree(compare, freeitem)))
	{
		fprintf(stderr, "%s: avl_alloc_tree(): %m\n", argv0),
		error = e_out_of_memory;
	}
	
	EXIT;
	return error;
}

