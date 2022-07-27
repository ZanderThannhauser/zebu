
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "set_default_transition.h"

void regex_set_default_transition(
	struct regex* from,
	struct regex* to)
{
	ENTER;
	
	assert(!from->default_transition_to);
	
	from->default_transition_to = to;
	
	EXIT;
}


