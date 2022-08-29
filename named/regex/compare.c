
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_regexes(const void* a, const void* b)
{
	const struct named_regex *A = a, *B = b;
	return strcmp(A->name, B->name);
}

