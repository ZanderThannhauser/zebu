
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_charsets(const void* a, const void* b)
{
	const struct named_charset* A = a, *B = b;
	return strcmp(A->name, B->name);
}

