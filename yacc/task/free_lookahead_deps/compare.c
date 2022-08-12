
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_free_lookahead_deps_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct free_lookahead_deps_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_free_lookahead_deps);
	assert(b->kind == tk_free_lookahead_deps);
	
	if (A->ldeps > B->ldeps)
		cmp = +1;
	else if (A->ldeps < B->ldeps)
		cmp = -1;
	
	return cmp;
}

