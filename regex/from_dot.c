
#include <debug.h>

#include "struct.h"
#include "new.h"
#include "from_dot.h"

struct regex* regex_from_dot()
{
	ENTER;
	
	struct regex* start = new_regex();
	
	struct regex* accepts = new_regex();
	
	for (unsigned i = 0, n = 256; i < n; i++)
		start->transitions[i] = accepts;
	
	accepts->accepts = true;
	
	EXIT;
	return start;
}
