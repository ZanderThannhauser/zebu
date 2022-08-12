
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_expand_tree_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct expand_tree_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_expand_tree);
	assert(b->kind == tk_expand_tree);
	
	if (A->state > B->state)
		cmp = +1;
	else if (A->state < B->state)
		cmp = -1;
	
	return cmp;
}

