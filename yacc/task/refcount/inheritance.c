
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance refcount_task_inheritance = {
	.compare = compare_refcount_tasks,
	.process = refcount_task_process,
	#ifdef DOTOUT
	.dotout = refcount_task_dotout,
	#endif
	.free = free_refcount_task,
};

