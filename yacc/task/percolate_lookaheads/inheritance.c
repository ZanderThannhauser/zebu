
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance percolate_lookaheads_task_inheritance = {
	.compare = compare_percolate_lookaheads_tasks,
	.process = percolate_lookaheads_task_process,
	#ifdef DEBUGGING
	.dotout = percolate_lookaheads_task_dotout,
	#endif
	.free = free_percolate_lookaheads_task,
};

