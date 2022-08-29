
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/set_default_transition.h"

#include "from_dot.h"

struct regex* regex_from_dot()
{
	ENTER;
	
	struct regex* start = new_regex();
	struct regex* end = new_regex();
	
	regex_set_default_transition(start, end);
	
	end->is_accepting = true;
	
	EXIT;
	return start;
}
