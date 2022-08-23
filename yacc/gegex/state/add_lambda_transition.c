
#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void gegex_add_lambda_transition(
	struct gegex* from,
	struct gegex* to)
{
	ENTER;
	
	dpv(from);
	dpv(to);
	
	struct memory_arena* const arena = from->arena;
	
	if (from->lambda_transitions.n + 1 > from->lambda_transitions.cap)
	{
		from->lambda_transitions.cap = from->lambda_transitions.cap * 2 ?: 1;
		
		dpv(from->lambda_transitions.cap);
		
		from->lambda_transitions.data = arena_realloc(
			arena, from->lambda_transitions.data,
			sizeof(*from->lambda_transitions.data) * from->lambda_transitions.cap);
	}
	
	from->lambda_transitions.data[from->lambda_transitions.n++] = to;
	
	EXIT;
}

















