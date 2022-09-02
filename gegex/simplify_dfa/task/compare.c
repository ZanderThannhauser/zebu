
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_gegex_simplify_tasks(const void* a, const void* b)
{
	const struct gegex_simplify_task* A = a, *B = b;
	int cmp;
	ENTER;
	
	dpv(A->hopcount);
	dpv(B->hopcount);
	
	if (A->hopcount > B->hopcount)
		cmp = +1;
	else if (A->hopcount < B->hopcount)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

