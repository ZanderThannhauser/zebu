
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance add_reductions_task_inheritance = {
	.compare = compare_add_reductions_tasks,
	.process = add_reductions_task_process,
	.dotout = add_reductions_task_dotout,
	.free = free_add_reductions_task,
};

