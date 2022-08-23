
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expand_tree_task* new_expand_tree_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct lookahead_deps* ldeps,
	struct gegex* state,
	const char* reduce_as,
	struct tokenset* lookaheads)
{
	ENTER;
	
	struct expand_tree_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_expand_tree,
		&expand_tree_task_inheritance,
		sizeof(*this));
	
	this->stateinfo = stateinfo;
	this->ldeps = ldeps;
	
	this->state = state;
	
	this->reduce_as = reduce_as;
	this->lookaheads = lookaheads;
	
	EXIT;
	return this;
}

