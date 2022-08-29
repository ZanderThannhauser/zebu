
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex* new_regex(
) {
	ENTER;
	
	struct regex* this = smalloc(sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	this->default_transition_to = NULL;
	
	this->EOF_transition_to = NULL;
	
	this->phase = 0;
	
	this->is_accepting = 0;
	
	this->priority = 0;
	
	EXIT;
	return this;
}
