
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "set_EOF_transition.h"

void lex_state_set_EOF_transition(
	struct lex_state* this,
	struct lex_state* to)
{
	assert(!this->EOF_transition_to);
	
	this->EOF_transition_to = to;
}

