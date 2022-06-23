
#include <debug.h>

#include "../../state/struct.h"

#include "struct.h"
#include "compare.h"

int compare_iterators(struct iterator* a, struct iterator* b)
{
	if (a->moving < a->end)
	{
		if (b->moving < b->end)
		{
			struct regex* const state_a = a->moving[0]->to;
			struct regex* const state_b = b->moving[0]->to;
			
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
		if (b->moving < b->end)
		{
			TODO;
		}
		else
		{
			TODO;
		}
	}
}

