
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_unsignedcharsets(
	const struct unsignedcharset* a,
	const struct unsignedcharset* b)
{
	struct avl_node_t *an = a->tree->head;
	struct avl_node_t *bn = b->tree->head;
	
	while (an && bn)
	{
		unsigned char ae = *(unsigned char*) an->item;
		unsigned char be = *(unsigned char*) bn->item;
		
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

