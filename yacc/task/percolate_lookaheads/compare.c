
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_percolate_lookaheads_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct percolate_lookaheads_task* A = (void*) a, *B = (void*) b;
	ENTER;
	
	assert(a->kind == tk_percolate_lookaheads);
	assert(b->kind == tk_percolate_lookaheads);
	
	cmp = strcmp(A->name, B->name);
	
	EXIT;
	return cmp;
}

