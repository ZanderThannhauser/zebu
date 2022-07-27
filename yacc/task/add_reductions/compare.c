
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_add_reductions_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct add_reductions_task* A = (void*) a, *B = (void*) b;
	ENTER;
	
	cmp = strcmp(A->name, B->name);
	
	EXIT;
	return cmp;
}

