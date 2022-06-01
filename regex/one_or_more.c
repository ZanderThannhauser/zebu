
#include <debug.h>

#include "state/struct.h"

#include "clone.h"
#include "lambda_all_accepting_states.h"
#include "one_or_more.h"

int regex_one_or_more(
	struct regex_state** out,
	struct memory_arena* arena,
	struct regex_state* in)
{
	int error = 0;
	ENTER;
	
	struct regex_state* clone;
	
	error = 0
		?: regex_clone(&clone, arena, in)
		?: regex_lambda_all_accepting_states(clone, arena, clone, false)
		?: regex_lambda_all_accepting_states(in, arena, clone, false);
	
	if (!error)
	{
		clone->is_accepting = true;
		*out = in;
	}
	
	EXIT;
	return error;
}

