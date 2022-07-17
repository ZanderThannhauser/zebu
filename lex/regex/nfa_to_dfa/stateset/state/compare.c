
#include <debug.h>

#include "compare.h"

int compare_states(const void* a, const void* b)
{
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}

