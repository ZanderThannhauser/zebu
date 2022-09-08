
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_regex_simplify_tasks(const void* a, const void* b)
{
	const struct regex_simplify_task* A = a, *B = b;
	int cmp;
	ENTER;
	
	if (A->hopcount > B->hopcount)
		cmp = +1;
	else if (A->hopcount < B->hopcount)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

