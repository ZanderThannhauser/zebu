
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "process.h"

void task_process(struct task* this, struct shared* shared)
{
	ENTER;
	
	assert(this->inheritance->process);
	
	(this->inheritance->process)(this, shared);
	
	EXIT;
}
