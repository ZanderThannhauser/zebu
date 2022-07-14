
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "compare.h"

int compare_tasks(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct task* A = a, *B = b;
	
	dpv(A->kind);
	dpv(B->kind);
	
	if (A->kind < B->kind)
		cmp = -1;
	else if (A->kind > B->kind)
		cmp = +1;
	else
	{
		assert(A->inheritance->compare);
		cmp = (A->inheritance->compare)(A, B);
	}
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

