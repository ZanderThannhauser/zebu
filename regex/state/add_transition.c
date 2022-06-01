
#include <debug.h>

#include <memory/arena/malloc.h>
#include <memory/arena/realloc.h>

#include "struct.h"
#include "add_transition.h"

int regex_state_add_transition(
	struct regex_state* from,
	struct memory_arena* arena,
	char value,
	struct regex_state* to)
{
	int error = 0;
	struct transition* transition = NULL;
	ENTER;
	
	error = arena_malloc(arena, (void**) &transition, sizeof(*transition));
	
	dpv(transition);
	
	if (!error)
	{
		transition->value = value;
		transition->to = to;
		
		if (from->transitions.n + 1 >= from->transitions.cap)
		{
			from->transitions.cap = from->transitions.cap * 2 ?: 1;
			
			error = arena_realloc(
				arena, (void**) &from->transitions.data,
				sizeof(*from->transitions.data) * from->transitions.cap);
		}
	}
	
	if (!error)
	{
		size_t i;
		struct transition** const data = from->transitions.data;
		
		for (i = from->transitions.n++ - 1;
			0 + 1 <= i + 1 && value < data[i]->value; i--)
		{
			data[i + 1] = data[i];
		}
		
		data[i + 1] = transition;
	}
	
	EXIT;
	return error;
}




















