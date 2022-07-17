
#include <debug.h>

#include <memory/arena/realloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void gegex_add_lambda_transition(
	struct gegex* from,
	struct memory_arena* arena,
	struct gegex* to)
{
	ENTER;
	
	dpv(from);
	dpv(to);
	
	if (from->lambda_transitions.n + 1 > from->lambda_transitions.cap)
	{
		from->lambda_transitions.cap = from->lambda_transitions.cap * 2 ?: 1;
		
		dpv(from->lambda_transitions.cap);
		
		from->lambda_transitions.data = arena_realloc(
			arena, from->lambda_transitions.data,
			sizeof(*from->lambda_transitions.data) * from->lambda_transitions.cap);
	}
	
	HERE;
	
	from->lambda_transitions.data[from->lambda_transitions.n++] = to;
	
	EXIT;
}

















