
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "accepts.h"

static int compare(const void* a, const void* b)
{
	const struct transition* A = a, *B = b;
	
	if (A->value > B->value)
		return +1;
	else if (A->value < B->value)
		return -1;
	else
		return +0;
}

bool regex_accepts(
	struct regex* start,
	unsigned char* data,
	unsigned n)
{
	ENTER;
	
	struct regex* moving = start;
	
	while (moving && n--)
	{
		assert(!moving->lambda_transitions.n);
		
		struct transition** to = bsearch(
			/* key: */ data++,
			/* base: */ moving->transitions.data,
			/* nmemb: */ moving->transitions.n,
			/* size: */ sizeof(*moving->transitions.data),
			/* compar: */ compare);
		
		if (to)
		{
			TODO;
		}
		else if (moving->default_transition_to)
		{
			moving = moving->default_transition_to;
		}
		else
		{
			moving = NULL;
		}
	}
	
	EXIT;
	bool retval = moving ? moving->is_accepting : 0;
	dpvb(retval);
	return retval;
}
















