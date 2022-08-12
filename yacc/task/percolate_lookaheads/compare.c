
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_percolate_lookaheads_tasks(const struct task* a, const struct task* b)
{
	const struct percolate_lookaheads_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_percolate_lookaheads);
	assert(b->kind == tk_percolate_lookaheads);
	
	if (A->state > B->state)
		return +1;
	else if (A->state < B->state)
		return -1;
	else
		return +0;
	
}

