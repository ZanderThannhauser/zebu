
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct build_ystate_task* new_build_ystate_task(
	struct yacc_state* state,
	struct yacc_stateinfo* stateinfo)
{
	ENTER;
	
	struct build_ystate_task* this = (void*) new_task(
		tk_build_ystate,
		&build_ystate_task_inheritance,
		sizeof(*this));
	
	this->state = state;
	
	this->stateinfo = stateinfo;
	
	EXIT;
	return this;
}

