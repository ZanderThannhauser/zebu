
#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex_transition* new_regex_transition(
	unsigned char value,
	struct regex* to
) {
	ENTER;
	
	struct regex_transition* this = smalloc(sizeof(*this));
	
	this->value = value;
	this->to = to;
	
	EXIT;
	return this;
}

