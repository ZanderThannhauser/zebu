
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <strset/new.h>

#include <named/strset/struct.h>
#include <named/strset/new.h>

#include "get_deps.h"

struct strset* get_deps(struct avl_tree_t* tree, const char* name)
{
	struct strset* retval;
	ENTER;
	
	dpvs(name);
	
	struct avl_node_t* node;
	if ((node = avl_search(tree, &name)))
	{
		struct named_strset* ns = node->item;
		retval = ns->strset;
	}
	else
	{
		retval = new_strset();
		struct named_strset* ns = new_named_strset(name, retval);
		avl_insert(tree, ns);
	}
	
	EXIT;
	return retval;
}

