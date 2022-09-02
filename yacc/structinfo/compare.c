
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_structinfos(const void* a, const void* b)
{
	const struct structinfo *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

