
#include <debug.h>

#include <avl/tree_t.h>

#include <string/are_equal.h>

#include "struct.h"
#include "are_equal.h"

bool stringsets_are_equal(
	const struct stringset* a,
	const struct stringset* b)
{
	ENTER;
	
	if (a->n != b->n)
	{
		EXIT;
		return false;
	}
	
	struct avl_node_t *an = a->tree->head;
	struct avl_node_t *bn = b->tree->head;
	
	for (unsigned i = 0, n = a->n; i < n; i++, an = an->next, bn = bn->next)
	{
		if (!strings_are_equal(an->item, bn->item))
		{
			EXIT;
			return false;
		}
	}
	
	EXIT;
	return true;
}













