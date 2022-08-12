
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_lookahead_deps_nodes(const void* a, const void* b)
{
	const struct lookahead_deps_node *A = a, *B = b;
	
	dpv(A->a);
	dpv(B->a);
	
	if (A->a > B->a)
		return +1;
	else if (A->a < B->a)
		return -1;
	else
		return +0;
}

