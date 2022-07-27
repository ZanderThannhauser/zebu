
#include <assert.h>

#include <debug.h>

#include "../../state/struct.h"

#include "struct.h"
#include "compare.h"

int compare_iterators(const void* a, const void* b)
{
	const struct iterator* A = a, *B = b;
	
	if (A->moving < A->end)
	{
		if (B->moving < B->end)
		{
			struct regex* const state_a = A->moving[0]->to;
			struct regex* const state_b = B->moving[0]->to;
			
			if (state_a > state_b)
				return 1;
			else if (state_a < state_b)
				return -1;
			else
				return 0;
		}
		else
		{
			TODO;
		}
	}
	else
	{
		if (B->moving < B->end)
		{
			TODO;
		}
		else
		{
			TODO;
		}
	}
}









