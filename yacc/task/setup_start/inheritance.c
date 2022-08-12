
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance setup_start_task_inheritance = {
	.compare = compare_setup_start_tasks,
	.process = setup_start_task_process,
	#ifdef DEBUGGING
	.dotout = setup_start_task_dotout,
	#endif
	.free = free_setup_start_task,
};

