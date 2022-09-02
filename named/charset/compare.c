
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_charsets(const void* a, const void* b)
{
	const struct named_charset *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

