
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance free_lookahead_deps_task_inheritance = {
	.compare = compare_free_lookahead_deps_tasks,
	.process = free_lookahead_deps_task_process,
	#ifdef DEBUGGING
	.dotout = free_lookahead_deps_task_dotout,
	#endif
	.free = free_free_lookahead_deps_task,
};

