
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/inc.h>

#include "struct.h"
#include "set_default_transition.h"

void lex_state_set_default_transition(
	struct lex_state* this,
	struct unsignedcharset* exceptions,
	struct lex_state* to)
{
	ENTER;
	
	assert(!this->default_transition.to);
	
	assert(exceptions);
	
	this->default_transition.exceptions = inc_unsignedcharset(exceptions);
	this->default_transition.to = to;
	
	EXIT;
}

