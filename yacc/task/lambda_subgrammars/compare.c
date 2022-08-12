
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_lambda_subgrammars_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct lambda_subgrammars_task* A = (void*) a, *B = (void*) b;
	
	if (A->node > B->node)
		cmp = +1;
	else if (A->node < B->node)
		cmp = -1;
	
	return cmp;
}

