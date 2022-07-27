
#include <stddef.h>

#include "kind.h"

struct task_inheritance;

struct task* new_task(
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size);
