
#include <debug.h>

#include "state/struct.h"
#include "state/new.h"

#include "from_dot.h"

struct regex* regex_from_dot()
{
	ENTER;
	
	struct regex* start = new_regex();
	
	struct regex* accepts = new_regex();
	
	for (unsigned i = 0, n = 256; i < n; i++)
		start->transitions[i] = accepts;
	
	accepts->is_accepting = true;
	
	EXIT;
	return start;
}
