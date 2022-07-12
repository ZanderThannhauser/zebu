
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "inheritance.h"

struct task_inheritance explore_firsts_task_inheritance = {
	.compare = compare_explore_firsts_tasks,
	.process = explore_firsts_task_process,
	.dotout = explore_firsts_task_dotout,
};

