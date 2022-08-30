
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/inc.h>

#include "struct.h"
#include "set_default_transition.h"

void regex_set_default_transition(
	struct regex* from,
	struct unsignedcharset* exceptions,
	struct regex* to)
{
	ENTER;
	
	assert(!from->default_transition.to);
	
	from->default_transition.exceptions = inc_unsignedcharset(exceptions);
	
	from->default_transition.to = to;
	
	EXIT;
}

