
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_yacc_stateinfo_nodes(const void* a, const void* b)
{
	const struct yacc_stateinfo_node* A = a, *B = b;
	
	if (A->state > B->state)
		return +1;
	else if (A->state < B->state)
		return -1;
	else
		return +0;
}

