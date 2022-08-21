
#include <debug.h>

#include "struct.h"
#include "new.h"

struct task* new_task(
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	TODO;
	#if 0
	struct task* this = smalloc(alloc_size);
	
	this->kind = kind;
	this->inheritance = inheritance;
	
	EXIT;
	return this;
	#endif
}

