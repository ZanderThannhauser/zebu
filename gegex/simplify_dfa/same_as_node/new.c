
#include <stdlib.h>
#include <debug.h>

#include "struct.h"
#include "new.h"

struct gegex_same_as_node* new_gegex_same_as_node(
	struct gegex* state, struct gegexset* set) {
	ENTER;
	
	struct gegex_same_as_node* this = malloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}
