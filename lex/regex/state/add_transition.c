
#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>

#include "struct.h"
#include "add_transition.h"

void regex_add_transition(
	struct regex* from,
	struct memory_arena* arena,
	unsigned value,
	struct regex* to)
{
	ENTER;
	
	struct transition* transition = arena_malloc(arena, sizeof(*transition));
	
	transition->value = value;
	transition->to = to;
	
	if (from->transitions.n + 1 >= from->transitions.cap)
	{
		from->transitions.cap = from->transitions.cap * 2 ?: 1;
		
		from->transitions.data = arena_realloc(
			arena, from->transitions.data,
			sizeof(*from->transitions.data) * from->transitions.cap);
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




















