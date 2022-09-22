
#if 0
#include <debug.h>

#include <avl/tree_t.h>

#include <string/compare.h>

#include "struct.h"
#include "are_equal.h"

bool structinfos_are_equal(
	const struct structinfo* a,
	const struct structinfo* b)
{
	struct avl_node_t* an = a->tree->head, *bn = b->tree->head;
	
	while (an && bn)
	{
		struct structinfo_node* ae = an->item, *be = bn->item;
		
		int cmp = compare_strings(ae->name, be->name);
		
		if (cmp) return false;
		
		an = an->next, bn = bn->next;
	}
	
	return !an && !bn;
}

#endif
