
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <set/of_strs/new.h>

#include <named/strset/struct.h>
#include <named/strset/new.h>

#include "get_firsts_deps.h"

struct strset* get_firsts_deps(struct avl_tree_t* tree, const char* name)
{
	struct strset* retval;
	
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
	
	return retval;
}

