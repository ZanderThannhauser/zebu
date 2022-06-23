
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "from_dot.h"

struct regex* regex_from_dot(struct memory_arena* arena)
{
	ENTER;
	
	struct regex* start = new_regex(arena);
	
	struct regex* end = new_regex(arena);
	
	regex_set_default_transition(start, end);
	
	end->is_accepting = true;
	
	EXIT;
	return start;
}

