
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <set/of_strs/new.h>
#include <set/of_strs/add.h>

#include <named/strset/struct.h>
#include <named/strset/new.h>

#include "struct.h"
#include "add_firsts_dep.h"

void add_firsts_dep(
	struct yacc_shared* shared,
	struct avl_tree_t* tree, const char* they, const char* need_me)
{
	ENTER;
	
	struct avl_node_t* node;
	
	if ((node = avl_search(tree, &they)))
	{
		struct named_strset* s = node->item;
		
		strset_add(s->strset, need_me);
	}
	else
	{
		#ifdef WITH_ARENAS
		struct strset* news = new_strset(shared->arena);
		#else
		struct strset* news = new_strset();
		#endif
		
		strset_add(news, need_me);
		
		#ifdef WITH_ARENAS
		avl_insert(tree, new_named_strset(shared->arena, they, news));
		#else
		avl_insert(tree, new_named_strset(they, news));
		#endif
	}
	
	EXIT;
}

