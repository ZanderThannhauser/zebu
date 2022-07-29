
#include <debug.h>

#include <memory/smalloc.h>

#include <set/of_regexes/clone.h>

#include "struct.h"
#include "new.h"

struct mapping* new_mapping(struct regexset* set, struct regex* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->original_states = regexset_clone(set);
	this->combined_state = state;
	
	EXIT;
	return this;
}

