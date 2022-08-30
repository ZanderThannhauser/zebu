
#include <debug.h>

#include "struct.h"
#include "are_equal.h"

bool unsignedcharset_are_equal(
	const struct unsignedcharset* a,
	const struct unsignedcharset* b)
{
	ENTER;
	
	if (a->n != b->n)
	{
		EXIT;
		return false;
	}
	
	for (struct avl_node_t *an = a->tree->head, *bn = b->tree->head;
		an; an = an->next, bn = bn->next)
	{
		unsigned char *ae = an->item, *be = bn->item;
		
		if (*ae != *be)
		{
			EXIT;
			return false;
		}
	}
	
	EXIT;
	return true;
}

