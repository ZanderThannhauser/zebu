
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance explore_lookaheads_task_inheritance = {
	.compare = compare_explore_lookaheads_tasks,
	.process = explore_lookaheads_task_process,
	.dotout = explore_lookaheads_task_dotout,
	.free = free_explore_lookaheads_task,
};

