
#include <debug.h>

/*#include <memory/arena/malloc.h>*/
/*#include <memory/arena/realloc.h>*/

#include "struct.h"
#include "add_transition.h"

void gegex_add_transition(
	struct gegex* from,
	struct memory_arena* arena,
	unsigned token,
	struct gegex* to)
{
	ENTER;
	
	TODO;
	#if 0
	struct transition* transition = arena_malloc(arena, sizeof(*transition));
	
	dpv(transition);
	
	transition->token = token;
	transition->to = to;
	
	if (from->transitions.n + 1 > from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		from->transitions.data = arena_realloc(
			arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
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
	#endif
}




















