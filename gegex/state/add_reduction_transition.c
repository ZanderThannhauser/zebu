
#include <assert.h>

#include <debug.h>

/*#include <memory/arena/malloc.h>*/
/*#include <memory/arena/realloc.h>*/

#include "struct.h"
#include "add_reduction_transition.h"

void gegex_add_reduction_transition(
	struct gegex* from,
	unsigned token,
	char* reduce_as,
	unsigned popcount)
{
	ENTER;
	
	TODO;
	#if 0
	struct rtransition* rtransition = arena_malloc(arena, sizeof(*rtransition));
	
	rtransition->token = token;
	rtransition->reduce_as = reduce_as;
	rtransition->popcount = popcount;
	
	if (from->reduction_transitions.n + 1 > from->reduction_transitions.cap)
	{
		from->reduction_transitions.cap = from->reduction_transitions.cap * 2 ?: 1;
		
		from->reduction_transitions.data = arena_realloc(
			arena, from->reduction_transitions.data,
			sizeof(*from->reduction_transitions.data)
			*from->reduction_transitions.cap);
	}
	
	size_t i;
	struct rtransition** const data = from->reduction_transitions.data;
	
	for (i = from->reduction_transitions.n++ - 1;
		0 + 1 <= i + 1 && token < data[i]->token; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = rtransition;
	
	EXIT;
	#endif
}




















