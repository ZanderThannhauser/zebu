
#include <stdio.h>
#include <stdlib.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <debug.h>

#include "tree_t.h"
#include "alloc_tree.h"
#include "new.h"

struct avl_tree_t* new_avl_tree(
	int (*compare)(const void *, const void *),
	void (*freeitem)(void *))
{
	ENTER;
	
	struct avl_tree_t* retval = avl_alloc_tree(compare, freeitem);
	
	if (!retval)
	{
		fprintf(stderr, "%s: avl_alloc_tree(): %m\n", argv0),
		exit(e_out_of_memory);
	}
	
	EXIT;
	return retval;
}

