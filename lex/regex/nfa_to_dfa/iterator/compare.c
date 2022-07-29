
#include <assert.h>

#include <debug.h>

#include "../../state/struct.h"

#include "struct.h"
#include "compare.h"

int compare_iterators(const void* a, const void* b)
{
	const struct iterator* A = a, *B = b;
	
	assert (A->moving < A->end);
	assert (B->moving < B->end);
	
	unsigned value_a = A->moving[0]->value;
	unsigned value_b = B->moving[0]->value;
	
	if (value_a > value_b)
		return +1;
	else if (value_a < value_b)
		return -1;
	else
		return 0;
}









