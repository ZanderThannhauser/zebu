
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_transition.h"

void gegex_add_transition(
	struct gegex* from,
	unsigned token,
	struct gegex* to)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = from->arena;
	
	struct transition* transition = arena_malloc(arena, sizeof(*transition));
	#else
	struct transition* transition = malloc(sizeof(*transition));
	#endif
	
	dpv(transition);
	
	transition->token = token;
	transition->to = to;
	
	if (from->transitions.n + 1 > from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		#ifdef WITH_ARENAS
		from->transitions.data = arena_realloc(
			arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
		#else
		from->transitions.data = realloc(from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
		#endif
	}
	
	size_t i;
	struct transition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1;
		0 + 1 <= i + 1 && token < data[i]->token; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}




















