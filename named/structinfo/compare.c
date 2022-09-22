
#include <debug.h>

#include <string/compare.h>

#include "struct.h"
#include "compare.h"

int compare_named_structinfos(const void* a, const void* b)
{
	ENTER;
	
	const struct named_structinfo *A = a, *B = b;
	
	int cmp = compare_strings(A->name, B->name);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

