
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct task* new_task(
	struct memory_arena* arena,
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	struct task* this = arena_malloc(arena, alloc_size);
	
	this->kind = kind;
	this->inheritance = inheritance;
	
	EXIT;
	return this;
}

