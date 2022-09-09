
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct regex_same_as_node* new_regex_same_as_node(
	struct regex* state, struct regexset* set)
{
	ENTER;
	
	struct regex_same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}
