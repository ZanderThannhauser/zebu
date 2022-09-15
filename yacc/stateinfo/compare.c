
#include <debug.h>

#include <avl/tree_t.h>

#include <set/unsigned/compare.h>

#include "node/struct.h"

#include "struct.h"
#include "compare.h"

int compare_stateinfo(
	const struct stateinfo *a,
	const struct stateinfo *b)
{
	TODO;
	#if 0
	struct avl_node_t *an = a->tree->head;
	struct avl_node_t *bn = b->tree->head;
	
	while (an && bn)
	{
		struct stateinfo_node* const ae = an->item;
		struct stateinfo_node* const be = bn->item;
		
		if (ae->trie > be->trie)
			return +1;
		else if (ae->trie < be->trie)
			return -1;
		else
		{
			int cmp = compare_unsignedsets(ae->lookaheads, be->lookaheads);
			
			if (cmp)
				return cmp;
			
			an = an->next;
			bn = bn->next;
		}
	}
	
	if (an)
		return +1;
	else if (bn)
		return -1;
	else
		return 0;
	#endif
}











