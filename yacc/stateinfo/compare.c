
#include <debug.h>

#include <avl/tree_t.h>

#include <set/of_tokens/compare.h>

#include "node/struct.h"

#include "struct.h"
#include "compare.h"

int compare_yacc_stateinfos(
	const struct yacc_stateinfo* a,
	const struct yacc_stateinfo* b)
{
	struct avl_node_t* a_moving = a->tree->head;
	struct avl_node_t* b_moving = b->tree->head;
	
	while (a_moving && b_moving)
	{
		struct yacc_stateinfo_node* a_ele = a_moving->item;
		struct yacc_stateinfo_node* b_ele = b_moving->item;
		
		if (a_ele->state > b_ele->state)
			return +1;
		else if (a_ele->state < b_ele->state)
			return -1;
		
		int cmp = compare_tokensets(a_ele->lookaheads, b_ele->lookaheads);
		
		if (cmp)
			return cmp;
		
		a_moving = a_moving->next;
		b_moving = b_moving->next;
	}
	
	if (a_moving)
		return +1;
	else if (b_moving)
		return -1;
	else
		return +0;
}











