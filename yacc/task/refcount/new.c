
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct refcount_task* new_refcount_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start, struct gegex* node)
{
	ENTER;
	
	struct refcount_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_refcount,
		&refcount_task_inheritance,
		sizeof(*this));
	
	this->start = start;
	this->node = node;
	
	EXIT;
	return this;
}

