
#include <assert.h>

#include <debug.h>

#include <named/tokenset/struct.h>

#include <avl/search.h>

#include "lookup_tokenset.h"

struct tokenset* lookup_tokenset(
	struct avl_tree_t* tree,
	const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node = avl_search(tree, &name);
	
	assert(node);
	
	struct named_tokenset* nt = node->item;
	
	EXIT;
	return nt->tokenset;
}

