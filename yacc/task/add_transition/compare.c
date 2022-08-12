
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_add_transition_tasks(const struct task* a, const struct task* b)
{
	const struct add_transition_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_add_transition);
	assert(b->kind == tk_add_transition);
	
	if (A->stateinfo > B->stateinfo)
		return +1;
	else if (A->stateinfo < B->stateinfo)
		return -1;
	else
		return 0;
}

