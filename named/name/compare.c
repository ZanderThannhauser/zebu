
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_names(const void* a, const void* b)
{
	const struct named_name* A = a, *B = b;
	return strcmp(A->name, B->name);
}

