
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct add_transition_task* new_add_transition_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_state** write_to_me,
	struct yacc_stateinfo* stateinfo)
{
	ENTER;
	
	struct add_transition_task* this = (void*) new_task(
		#ifdef WITH_ARENAS
		arena,
		#endif
		tk_add_transition,
		&add_transition_task_inheritance,
		sizeof(*this));
	
	this->write_to_me = write_to_me;
	this->stateinfo = stateinfo;
	
	EXIT;
	return this;
}

