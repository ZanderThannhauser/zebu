
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct stateinfo_to_state* new_stateinfo_to_state(
	struct yacc_stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	struct stateinfo_to_state* this = smalloc(sizeof(*this));
	
	this->stateinfo = stateinfo;
	this->state = state;
	
	EXIT;
	return this;
}

