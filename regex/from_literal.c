
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"

#include "from_literal.h"

int regex_from_literal(
	struct regex_state** out,
	struct memory_arena* arena,
	const char* string,
	size_t len)
{
	int error = 0;
	ENTER;
	
	struct regex_state* start = NULL;
	
	error = new_regex_state(&start, arena);
	
	struct regex_state* accept = start;
	
	while (!error && len--)
	{
		struct regex_state* temp = NULL;
		
		error = 0
			?: new_regex_state(&temp, arena)
			?: regex_state_add_transition(accept, arena, *string++, temp);
		
		accept = temp;
	}
	
	if (!error)
	{
		accept->is_accepting = true;
		
		*out = start;
	}
	
	EXIT;
	return error;
}

