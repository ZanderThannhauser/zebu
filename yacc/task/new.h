
#include <stddef.h>

#include "kind.h"

struct memory_arena;
struct task_inheritance;

struct task* new_task(
	struct memory_arena* arena,
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size);
