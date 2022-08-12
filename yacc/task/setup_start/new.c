
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct setup_start_task* new_setup_start_task()
{
	ENTER;
	
	struct setup_start_task* this = (void*) new_task(
		tk_setup_start,
		&setup_start_task_inheritance,
		sizeof(*this));
	
	EXIT;
	return this;
}

