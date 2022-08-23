
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct build_ystate_task* new_build_ystate_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_state* state,
	struct yacc_stateinfo* stateinfo)
{
	ENTER;
	
	struct build_ystate_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_build_ystate,
		&build_ystate_task_inheritance,
		sizeof(*this));
	
	this->state = state;
	
	this->stateinfo = stateinfo;
	
	EXIT;
	return this;
}

