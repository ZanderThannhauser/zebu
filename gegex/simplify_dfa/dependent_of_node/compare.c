
#include <debug.h>

#include "../pair/compare.h"

#include "struct.h"
#include "compare.h"

int compare_gegex_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct gegex_dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_gegex_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}

