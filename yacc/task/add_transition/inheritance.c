
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance add_transition_task_inheritance = {
	.compare = compare_add_transition_tasks,
	.process = add_transition_task_process,
	#ifdef DEBUGGING
	.dotout = add_transition_task_dotout,
	#endif
	.free = free_add_transition_task,
};

