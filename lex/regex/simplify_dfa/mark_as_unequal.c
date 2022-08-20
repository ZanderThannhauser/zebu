
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <tree/of_regexes/contains.h>
#include <tree/of_regexes/discard.h>

#include "pair/struct.h"

#include "same_as_node/struct.h"

#include "mark_as_unequal.h"

bool simplify_dfa_mark_as_unequal(
	struct avl_tree_t* connections,
	struct pair* pair)
{
	ENTER;
	
	struct avl_node_t* a_node = avl_search(connections, &pair->a);
	struct avl_node_t* b_node = avl_search(connections, &pair->b);
	
	assert(a_node && b_node);
	
	struct same_as_node* a_sa = a_node->item, *b_sa = b_node->item;
	
	bool removed = false;
	
	if (regextree_contains(a_sa->set, pair->b))
	{
		assert(regextree_contains(b_sa->set, pair->a));
		
		regextree_discard(a_sa->set, pair->b);
		regextree_discard(b_sa->set, pair->a);
		
		removed = true;
	}
	
	dpvb(removed);
	
	EXIT;
	return removed;
}














