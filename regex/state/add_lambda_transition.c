
#include <debug.h>

#include <memory/arena/realloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

int regex_state_add_lambda_transition(
	struct regex_state* from,
	struct memory_arena* arena,
	struct regex_state* to)
{
	int error = 0;
	ENTER;
	
	if (from->lambda_transitions.n + 1 >= from->lambda_transitions.cap)
	{
		from->lambda_transitions.cap = from->lambda_transitions.cap * 2 ?: 1;
		
		error = arena_realloc(
			arena, (void**) &from->lambda_transitions.data,
			sizeof(*from->lambda_transitions.data) * from->lambda_transitions.cap);
	}
	
	if (!error)
	{
		from->lambda_transitions.data[from->lambda_transitions.n++] = to;
	}
	
	
	EXIT;
	return error;
}

















