
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "set_EOF_transition.h"

void regex_set_EOF_transition(
	struct regex* from,
	struct regex* to)
{
	ENTER;
	
	assert(!from->EOF_transition_to);
	
	from->EOF_transition_to = to;
	
	EXIT;
}


