
#include <debug.h>

#include <macros/min.h>

#include "struct.h"
#include "to_string.h"
#include "compare.h"

int compare_tokensets(
	const struct tokenset* a,
	const struct tokenset* b)
{
	int cmp = 0;
	
	for (unsigned i = 0, n = min(a->n, b->n); !cmp && i < n; i++)
	{
		unsigned a_ele = a->data[i], b_ele = b->data[i];
		
		if (a_ele > b_ele)
			cmp = +1;
		else if (a_ele < b_ele)
			cmp = -1;
	}
	
	if (!cmp)
	{
		if (a->n > b->n)
			cmp = +1;
		else if (a->n < b->n)
			cmp = -1;
	}
	
	return cmp;
}

