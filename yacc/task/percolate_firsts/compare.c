
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_percolate_firsts_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct percolate_firsts_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_percolate_firsts);
	assert(b->kind == tk_percolate_firsts);
	
	cmp = strcmp(A->name, B->name);
	
	return cmp;
}

