
#include <debug.h>

#include <string/compare.h>

#include "struct.h"
#include "compare.h"

int compare_named_gegexes(const void* a, const void* b)
{
	const struct named_gegex *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

