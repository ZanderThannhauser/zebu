
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_regex_pairs(const void* a, const void* b)
{
	int cmp = 0;
	const struct regex_pair *A = a, *B = b;
	ENTER;
	
	if (A->a > B->a)
		cmp = +1;
	else if (A->a < B->a)
		cmp = -1;
	else if (A->b > B->b)
		cmp = +1;
	else if (A->b < B->b)
		cmp = -1;
	
	EXIT;
	return cmp;
}

