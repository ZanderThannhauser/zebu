
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "compare.h"

int compare_unsignedsets(const void* a, const void* b)
{
	const struct unsignedset *A = a, *B = b;
	
	struct avl_node_t *an = A->tree->head;
	struct avl_node_t *bn = B->tree->head;
	
	while (an && bn)
	{
		unsigned ae = *(unsigned*) an->item;
		unsigned be = *(unsigned*) bn->item;
		
		if (ae > be)
			return +1;
		else if (ae < be)
			return -1;
		else
		{
			an = an->next;
			bn = bn->next;
		}
	}
	
	if (an)
		return +1;
	else if (bn)
		return -1;
	else
		return +0;
}

