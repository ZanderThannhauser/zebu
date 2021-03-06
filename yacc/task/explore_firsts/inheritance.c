
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance explore_firsts_task_inheritance = {
	.compare = compare_explore_firsts_tasks,
	.process = explore_firsts_task_process,
	#ifdef DEBUGGING
	.dotout = explore_firsts_task_dotout,
	#endif
	.free = free_explore_firsts_task,
};

