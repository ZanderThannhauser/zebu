
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_strsets(const void* a, const void* b)
{
	const struct named_strset* A = a, *B = b;
	return strcmp(A->name, B->name);
}

