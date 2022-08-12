
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_setup_start_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct setup_start_task* A = (void*) a, *B = (void*) b;
	
	TODO;
	#if 0
	assert(a->kind == tk_setup_start);
	assert(b->kind == tk_setup_start);
	
	if (A->node > B->node)
		cmp = +1;
	else if (A->node < B->node)
		cmp = -1;
	
	return cmp;
	#endif
}

