
#include <debug.h>

#include "../pair/compare.h"

#include "struct.h"
#include "compare.h"

int compare_regex_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct regex_dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_regex_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}

