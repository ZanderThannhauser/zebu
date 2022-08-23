
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "compare.h"

int compare_gegextrees(
	struct gegextree* a,
	struct gegextree* b)
{
	struct avl_node_t* an = a->tree->head, *bn = b->tree->head;
	ENTER;
	
	while (an && bn)
	{
		struct gegex* const ae = an->item, *const be = bn->item;
		
		if (ae > be)
		{
			EXIT;
			return +1;
		}
		else if (ae < be)
		{
			EXIT;
			return -1;
		}
		else
		{
			an = an->next, bn = bn->next;
		}
	}
	
	if (an > bn)
	{
		EXIT;
		return +1;
	}
	else if (an < bn)
	{
		EXIT;
		return -1;
	}
	else
	{
		EXIT;
		return 0;
	}
}

