
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct lambda_subgrammars_task* new_lambda_subgrammars_task(
	const char* name,
	struct gegex* node,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	dpvs(name);
	
	struct lambda_subgrammars_task* this = (void*) new_task(
		tk_lambda_subgrammars,
		&lambda_subgrammars_task_inheritance,
		sizeof(*this));
	
	this->name = name;
	this->node = node;
	this->scratchpad = scratchpad;
	
	EXIT;
	return this;
}

