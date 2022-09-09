
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_strings(const void* a, const void* b)
{
	const struct string *A = a, *B = b;
	dpvs(A->chars);
	dpvs(B->chars);
	return strcmp(A->chars, B->chars);
}

