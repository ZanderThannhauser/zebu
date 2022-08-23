
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_transition.h"

void lex_state_add_transition(
	struct lex_state* from,
	unsigned char value,
	struct lex_state* to)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = from->arena;
	
	struct ltransition* transition = arena_malloc(arena, sizeof(*transition));
	#else
	struct ltransition* transition = malloc(sizeof(*transition));
	#endif
	
	dpv(transition);
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 >= from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		dpv(from->transitions.cap );
		
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
	struct ltransition** const data = from->transitions.data;
	
	for (i = from->transitions.n++ - 1;
		0 + 1 <= i + 1 && value < data[i]->value; i--)
	{
		data[i + 1] = data[i];
	}
	
	data[i + 1] = transition;
	
	EXIT;
}

