
#include <debug.h>

#include <defines/argv0.h>

#include "avl.h"
#include "safe_insert.h"

void safe_avl_insert(struct avl_tree_t* tree, void* element)
{
	if (!avl_insert(tree, element))
	{
		fprintf(stderr, "%s: malloc(): %m\n", argv0);
		exit(e_out_of_memory);
	}
}

