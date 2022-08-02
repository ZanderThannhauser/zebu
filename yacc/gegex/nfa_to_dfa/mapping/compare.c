
#include <debug.h>

#include <set/of_gegexes/compare.h>

#include "struct.h"
#include "compare.h"

int compare_gegex_mappings(const void* a, const void* b)
{
	const struct gegex_mapping *A = a, *B = b;
	
	return compare_gegexsets(A->original_states, B->original_states);
}

