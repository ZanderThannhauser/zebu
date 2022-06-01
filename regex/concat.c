
#include <debug.h>

#include "dotout.h"
#include "lambda_all_accepting_states.h"
#include "concat.h"

int regex_concat(
	struct memory_arena* arena,
	struct regex_state* left,
	struct regex_state* right)
{
	int error = 0;
	ENTER;
	
	dpv(left);
	dpv(right);
	
	error = regex_lambda_all_accepting_states(
		/* regex: */ left,
		/* arena: */ arena,
		/* dest:  */ right,
		/* keep_accepting: */ false);
	
	#ifdef DEBUGGING
	if (!error)
		regex_dotout(left);
	#endif
	
	EXIT;
	return error;
}

