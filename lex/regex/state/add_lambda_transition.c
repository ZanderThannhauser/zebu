
#include <debug.h>

#include <arena/realloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void regex_add_lambda_transition(
	struct regex* from,
	struct regex* to)
{
	ENTER;
	
	if (from->lambda_transitions.n + 1 >= from->lambda_transitions.cap)
	{
		from->lambda_transitions.cap = from->lambda_transitions.cap * 2 ?: 1;
		
		from->lambda_transitions.data = arena_realloc(
			from->arena, from->lambda_transitions.data,
			sizeof(*from->lambda_transitions.data) * from->lambda_transitions.cap);
	}
	
	from->lambda_transitions.data[from->lambda_transitions.n++] = to;
	
	EXIT;
}

















