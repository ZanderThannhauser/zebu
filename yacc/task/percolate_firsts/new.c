
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct percolate_firsts_task* new_percolate_firsts_task(
	struct memory_arena* arena,
	const char* name)
{
	ENTER;
	
	dpvs(name);
	
	struct percolate_firsts_task* this = (void*) new_task(
		arena,
		tk_percolate_firsts,
		&percolate_firsts_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	
	EXIT;
	return this;
}

