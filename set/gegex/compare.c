
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "compare.h"

int compare_gegexsets(
	const struct gegexset* a,
	const struct gegexset* b)
{
	int cmp = 0;
	ENTER;
	
	struct avl_node_t* an = a->tree->head, *bn = b->tree->head;
	
	while (!cmp && an && bn)
	{
		struct gegex* ae = an->item;
		struct gegex* be = bn->item;
		
		if (ae > be)
			cmp = +1;
		else if (ae < be)
			cmp = -1;
		else
			an = an->next, bn = bn->next;
	}
	
	if (!cmp)
	{
		if (an)
			cmp = +1;
		else if (bn)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
}

