
#include <debug.h>

#include "../pair/compare.h"

#include "struct.h"
#include "compare.h"

int compare_lex_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct lex_dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_lex_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}

