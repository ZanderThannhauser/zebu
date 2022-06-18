
#include <debug.h>

#include "state/struct.h"

#include "clone.h"
#include "dotout.h"
#include "lambda_all_accepting_states.h"
#include "one_or_more.h"

struct regex* regex_one_or_more(
	struct memory_arena* arena,
	struct regex* in)
{
	int error = 0;
	ENTER;
	
	struct regex* clone = regex_clone(arena, in);
	
	regex_lambda_all_accepting_states(clone, arena, clone, false);
	
	regex_lambda_all_accepting_states(in, arena, clone, false);
	
	clone->is_accepting = true;
	
	#ifdef DEBUGGING
	if (!error)
		regex_dotout(in);
	#endif
	
	EXIT;
	return in;
}








