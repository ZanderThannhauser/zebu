
#include <debug.h>

#include <tree/of_gegexes/compare.h>

#include "struct.h"
#include "compare.h"

int compare_gegex_mappings(const void* a, const void* b)
{
	const struct gegex_mapping *A = a, *B = b;
	
	return compare_gegextrees(A->original_states, B->original_states);
}

