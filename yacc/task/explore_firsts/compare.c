
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_explore_firsts_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct explore_firsts_task* A = (void*) a, *B = (void*) b;
	ENTER;
	
	assert(a->kind == tk_explore_firsts);
	assert(b->kind == tk_explore_firsts);
	
	cmp = strcmp(A->name, B->name);
	
	if (!cmp)
	{
		if (A->node > B->node)
			cmp = +1;
		else if (A->node < B->node)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
}

