
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_regex_caches(const void* a, const void* b)
{
	const struct regex_cache *A = a, *B = b;
	
	if (A->a > B->a)
		return +1;
	else if (A->a < B->a)
		return -1;
	else if (A->b > B->b)
		return +1;
	else if (A->b < B->b)
		return -1;
	
	return 0;
}
