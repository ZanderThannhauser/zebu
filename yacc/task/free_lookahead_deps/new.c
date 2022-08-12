
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct free_lookahead_deps_task* new_free_lookahead_deps_task(
	struct lookahead_deps* ldeps)
{
	ENTER;
	
	struct free_lookahead_deps_task* this = (void*) new_task(
		tk_free_lookahead_deps,
		&free_lookahead_deps_task_inheritance,
		sizeof(*this));
	
	this->ldeps = ldeps;
	
	EXIT;
	return this;
}

