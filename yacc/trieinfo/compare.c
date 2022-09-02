
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_trieinfos(const void* a, const void* b)
{
	const struct trieinfo *A = a, *B = b;
	return strcmp(A->name, B->name);
}

