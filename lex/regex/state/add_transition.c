
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_transition.h"

void regex_add_transition(
	struct regex* from,
	unsigned value,
	struct regex* to)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct transition* transition = arena_malloc(from->arena, sizeof(*transition));
	#else
	struct transition* transition = malloc(sizeof(*transition));
	#endif
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 >= from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		#ifdef WITH_ARENAS
		from->transitions.data = arena_realloc(
			from->arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
		#else
		from->transitions.data = realloc(from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
		#endif
	}
	
	size_t i;
	struct transition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1;
		0 + 1 <= i + 1 && value < data[i]->value; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}




















