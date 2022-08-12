
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_build_ystate_tasks(const struct task* a, const struct task* b)
{
	const struct build_ystate_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_build_ystate);
	assert(b->kind == tk_build_ystate);
	
	if (A->state > B->state)
		return +1;
	else if (A->state < B->state)
		return -1;
	else
		return 0;
}

