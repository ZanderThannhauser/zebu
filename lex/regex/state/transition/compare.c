
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_regex_transitions(const void* a, const void* b)
{
	const struct regex_transition *A = a, *B = b;
	
	if (A->value > B->value)
		return +1;
	else if (A->value < B->value)
		return -1;
	else
		return +0;
}

