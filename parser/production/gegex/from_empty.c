
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_lambda_transition.h"

#include "from_empty.h"

struct bundle gegex_from_empty(
	struct memory_arena* arena)
{
	ENTER;
	
	struct gegex* start = new_gegex(arena);
	struct gegex* end = new_gegex(arena);
	
	gegex_add_lambda_transition(start, arena, end);
	
	EXIT;
	return (struct bundle) {start, end};
}

