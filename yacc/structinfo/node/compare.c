
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_structinfo_nodes(const void* a, const void* b)
{
	const struct structinfo_node *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

