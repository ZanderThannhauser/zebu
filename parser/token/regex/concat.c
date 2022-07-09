
#if 0
#include <debug.h>

#include "dotout.h"
#include "lambda_all_accepting_states.h"
#include "concat.h"

void regex_concat(
	struct memory_arena* arena,
	struct regex* left,
	struct regex* right)
{
	ENTER;
	
	regex_lambda_all_accepting_states(
		/* regex: */ left,
		/* arena: */ arena,
		/* dest:  */ right,
		/* new_accepting: */ false);
	
	#ifdef DEBUGGING
	regex_dotout(left);
	#endif
	
	EXIT;
}

#endif
