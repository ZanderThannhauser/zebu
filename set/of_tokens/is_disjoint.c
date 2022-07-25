
#include <debug.h>

#include "struct.h"
#include "is_disjoint.h"

bool tokenset_is_disjoint(
	const struct tokenset* a,
	const struct tokenset* b)
{
	bool is_disjoint = true;
	ENTER;
	
	unsigned i = 0, n = a->n;
	unsigned j = 0, m = b->n;
	
	while (is_disjoint && i < n && j < m)
	{
		unsigned a_ele = a->data[i];
		unsigned b_ele = b->data[i];
		
		dpv(a_ele);
		dpv(b_ele);
		
		TODO;
	}
	
	EXIT;
	return is_disjoint;
}

