
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct percolate_lookaheads_task* new_percolate_lookaheads_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct gegex* state,
	struct lookahead_deps* ldeps)
{
	ENTER;
	
	struct percolate_lookaheads_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_percolate_lookaheads,
		&percolate_lookaheads_task_inheritance,
		sizeof(*this));
	
	this->stateinfo = stateinfo;
	this->state = state;
	this->ldeps = ldeps;
	
	EXIT;
	return this;
}

