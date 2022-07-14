
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct add_reductions_task* new_add_reductions_task(
	const char* name,
	struct gegex* end,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	dpvs(name);
	
	struct add_reductions_task* this = (void*) new_task(
		tk_add_reductions,
		&add_reductions_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	this->end = end;
	this->scratchpad = scratchpad;
	
	EXIT;
	return this;
}

