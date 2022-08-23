
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <set/of_gegexes/add.h>

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "add.h"

static void add(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* tree,
	struct gegex* a,
	struct gegex* b)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &a);
	
	if (node)
	{
		struct lookahead_deps_node* old = node->item;
		
		gegexset_add(old->b, b);
	}
	else
	{
		#ifdef WITH_ARENAS
		struct lookahead_deps_node* new = new_lookahead_deps_node(arena, a, b);
		#else
		struct lookahead_deps_node* new = new_lookahead_deps_node(a, b);
		#endif
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

void lookahead_deps_add(
	struct lookahead_deps* this,
	struct gegex* I,
	struct gegex* feed_them)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	add(this->arena, this->dependant_of, I, feed_them);
	add(this->arena, this->dependant_on, feed_them, I);
	#else
	add(this->dependant_of, I, feed_them);
	add(this->dependant_on, feed_them, I);
	#endif
	
	EXIT;
}













