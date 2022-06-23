
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_nodes(const void* a, const void* b)
{
	int cmp;
	ENTER;
	
	const struct node* A = a, *B = b;
	
	if (A->id > B->id)
		cmp = +1;
	else if (A->id < B->id)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}


