
#include <debug.h>

#include <avl/search.h>

#include <set/of_gegexes/add.h>

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "add.h"

static void add(
	struct avl_tree_t* tree,
	struct gegex* a,
	struct gegex* b)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(tree, &a);
	
	if (node)
	{
		struct lookahead_deps_node* old = node->item;
		gegexset_add(old->b, b);
	}
	else
	{
		struct lookahead_deps_node* new = new_lookahead_deps_node(a, b);
		safe_avl_insert(tree, new);
	}
	#endif
	
	EXIT;
}

void lookahead_deps_add(
	struct lookahead_deps* this,
	struct gegex* I,
	struct gegex* feed_them)
{
	ENTER;
	
	add(this->dependant_of, I, feed_them);
	add(this->dependant_on, feed_them, I);
	
	EXIT;
}

