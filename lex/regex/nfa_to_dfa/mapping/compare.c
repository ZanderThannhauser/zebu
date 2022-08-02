
#include <debug.h>

#include <set/of_regexes/compare.h>

#include "struct.h"
#include "compare.h"

int compare_regex_mappings(const void* a, const void* b)
{
	const struct regex_mapping *A = a, *B = b;
	
	return compare_regexsets(A->original_states, B->original_states);
}

