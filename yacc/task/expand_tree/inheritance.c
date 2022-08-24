
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance expand_tree_task_inheritance = {
	.compare = compare_expand_tree_tasks,
	.process = expand_tree_task_process,
	#ifdef DOTOUT
	.dotout = expand_tree_task_dotout,
	#endif
	.free = free_expand_tree_task,
};

