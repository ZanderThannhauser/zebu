
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <strset/new.h>
#include <strset/add.h>

#include <named/strset/struct.h>
#include <named/strset/new.h>

#include "add_dep.h"

void add_dep(struct avl_tree_t* tree, const char* they, const char* need_me)
{
	ENTER;
	
	dpvs(they);
	dpvs(need_me);
	
	struct avl_node_t* node;
	if ((node = avl_search(tree, &they)))
	{
		struct named_strset* s = node->item;
		strset_add(s->strset, need_me);
	}
	else
	{
		struct strset* news = new_strset();
		strset_add(news, need_me);
		avl_insert(tree, new_named_strset(they, news));
	}
	
	EXIT;
}

