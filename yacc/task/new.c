
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct task* new_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size)
{
	ENTER;
	
	#ifdef WTIH_ARENAS
	struct task* this = arena_malloc(arena, alloc_size);
	#else
	struct task* this = malloc(alloc_size);
	#endif
	
	this->kind = kind;
	this->inheritance = inheritance;
	
	EXIT;
	return this;
}

