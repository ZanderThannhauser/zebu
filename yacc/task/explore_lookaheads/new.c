
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct explore_lookaheads_task* new_explore_lookaheads_task(
	struct gegex* start,
	const char* name,
	struct gegex* node,
	const char* invocation,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	dpvs(name);
	
	struct explore_lookaheads_task* this = (void*) new_task(
		tk_explore_lookaheads,
		&explore_lookaheads_task_inheritance,
		sizeof(*this));
	
	this->start = start;
	this->name = name;
	this->node = node;
	this->invocation = invocation;
	this->scratchpad = scratchpad;
	
	EXIT;
	return this;
}

