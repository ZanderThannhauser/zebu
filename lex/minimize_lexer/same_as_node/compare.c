
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_lex_same_as_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct lex_same_as_node* A = a, *B = b;
	ENTER;
	
	if (A->state > B->state)
		cmp = +1;
	else if (A->state < B->state)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

