
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct lex_state* new_lex_state()
{
	ENTER;
	
	struct lex_state* this = smalloc(sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->default_transition.exceptions = NULL;
	this->default_transition.to = NULL;
	
	this->EOF_transition_to = NULL;
	
	this->accepts = NULL;
	
	EXIT;
	return this;
}
