
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance build_ystate_task_inheritance = {
	.compare = compare_build_ystate_tasks,
	.process = build_ystate_task_process,
	#ifdef DEBUGGING
	.dotout = build_ystate_task_dotout,
	#endif
	.free = free_build_ystate_task,
};

