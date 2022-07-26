
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct mapping* new_mapping(struct regexset* set, struct regex* state)
{
	ENTER;
	struct mapping* this = smalloc(sizeof(*this));
	
	this->original_states = set;
	this->combined_state = state;
	
	EXIT;
	return this;
}

