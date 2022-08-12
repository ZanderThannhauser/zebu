
#include <debug.h>

#include <macros/min.h>

#include "struct.h"
#include "compare.h"

int compare_regexsets(
	const struct regexset* a,
	const struct regexset* b)
{
	int cmp = 0;
	
	for (unsigned i = 0, n = min(a->n, b->n); !cmp && i < n; i++)
	{
		struct regex* a_ele = a->data[i];
		struct regex* b_ele = b->data[i];
		
		if (a_ele > b_ele)
			cmp = +1;
		else if (a_ele < b_ele)
			cmp = -1;
	}
	
	if (!cmp)
	{
		unsigned a_n = a->n, b_n = b->n;
		
		if (a_n > b_n)
			cmp = +1;
		else if (a_n < b_n)
			cmp = -1;
	}
	
	return cmp;
}

