
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance percolate_firsts_task_inheritance = {
	.compare = compare_percolate_firsts_tasks,
	.process = percolate_firsts_task_process,
	#ifdef DEBUGGING
	.dotout = percolate_firsts_task_dotout,
	#endif
	.free = free_percolate_firsts_task,
};

