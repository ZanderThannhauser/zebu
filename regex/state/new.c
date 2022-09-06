
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex* new_regex()
{
	ENTER;
	
	struct regex* this = smalloc(sizeof(*this));
	
	memset(this->transitions, 0, sizeof(this->transitions));
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	this->EOF_transition_to = NULL;
	
	this->is_accepting = 0;
	
	this->is_literal = false;
	
	EXIT;
	return this;
}
