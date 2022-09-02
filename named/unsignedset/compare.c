
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_unsignedsets(const void* a, const void* b)
{
	const struct named_unsignedset *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

