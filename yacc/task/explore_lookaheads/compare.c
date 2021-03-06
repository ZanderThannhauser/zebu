
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_explore_lookaheads_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct explore_lookaheads_task* A = (void*) a, *B = (void*) b;
	ENTER;
	
	assert(a->kind == tk_explore_lookaheads);
	assert(b->kind == tk_explore_lookaheads);
	
	cmp = strcmp(A->name, B->name);
	
	if (!cmp)
	{
		if (!!A->invocation > !!B->invocation)
			cmp = +1;
		else if (!!A->invocation < !!B->invocation)
			cmp = -1;
		else if (A->invocation && B->invocation)
			cmp = strcmp(A->invocation, B->invocation);
	}
	
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

