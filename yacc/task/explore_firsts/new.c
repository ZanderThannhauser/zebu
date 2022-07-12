
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct explore_firsts_task* new_explore_firsts_task(
	const char* name,
	struct gegex* node)
{
	ENTER;
	
	dpvs(name);
	
	struct explore_firsts_task* this = (void*) new_task(
		tk_explore_firsts,
		&explore_firsts_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	this->node = node;
	
	EXIT;
	return this;
}

