
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct percolate_lookaheads_task* new_percolate_lookaheads_task(const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct percolate_lookaheads_task* this = (void*) new_task(
		tk_percolate_lookaheads,
		&percolate_lookaheads_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	
	EXIT;
	return this;
}

