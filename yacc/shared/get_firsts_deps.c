
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <set/of_strs/new.h>

#include <named/strset/struct.h>
#include <named/strset/new.h>

#include "struct.h"
#include "get_firsts_deps.h"

struct strset* get_firsts_deps(
	struct yacc_shared* shared,
	struct avl_tree_t* tree, const char* name)
{
	struct strset* retval;
	ENTER;
	
	struct avl_node_t* node;
	
	if ((node = avl_search(tree, &name)))
	{
		struct named_strset* ns = node->item;
		
		retval = ns->strset;
	}
	else
	{
		#ifdef WITH_ARENAS
		retval = new_strset(shared->arena);
		#else
		retval = new_strset();
		#endif
		
		#ifdef WITH_ARENAS
		struct named_strset* ns = new_named_strset(shared->arena, name, retval);
		#else
		struct named_strset* ns = new_named_strset(name, retval);
		#endif
		
		avl_insert(tree, ns);
	}
	
	EXIT;
	return retval;
}

