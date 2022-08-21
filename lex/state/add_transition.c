
#include <debug.h>

/*#include <memory/arena/malloc.h>*/
/*#include <memory/arena/realloc.h>*/

#include "struct.h"
#include "add_transition.h"

void lex_state_add_transition(
	struct lex_state* from,
	struct memory_arena* arena,
	unsigned char value,
	struct lex_state* to)
{
	ENTER;
	
	TODO;
	#if 0
	struct ltransition* transition = arena_malloc(arena, sizeof(*transition));
	
	dpv(transition);
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 >= from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		dpv(from->transitions.cap );
		
		from->transitions.data = arena_realloc(
			arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
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
	#endif
}

