
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct same_as_node* new_same_as_node(struct regex* state, struct regextree* set)
{
	ENTER;
	
	struct same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}

