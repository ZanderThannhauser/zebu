
#include <debug.h>

#include "struct.h"
#include "set_default_transition.h"

void lex_state_set_default_transition(
	struct lex_state* this,
	struct lex_state* default_transition_to)
{
	ENTER;
	
	assert(!this->default_transition_to);
	
	this->default_transition_to = default_transition_to;
	
	EXIT;
}

