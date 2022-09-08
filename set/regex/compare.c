
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_regexsets(
	const struct regexset* a,
	const struct regexset* b)
{
	int cmp = 0;
	ENTER;
	
	struct avl_node_t* anode = a->tree->head;
	struct avl_node_t* bnode = b->tree->head;
	
	while (!cmp && anode && bnode)
	{
		struct regex* aele = anode->item;
		struct regex* bele = bnode->item;
		
		if (aele > bele)
			cmp = +1;
		else if (aele < bele)
			cmp = -1;
		else
		{
			anode = anode->next;
			bnode = bnode->next;
		}
	}
	
	if (!cmp)
	{
		if (anode)
			cmp = +1;
		else if (bnode)
			cmp = -1;
	}
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

