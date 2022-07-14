
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance lambda_subgrammars_task_inheritance = {
	.compare = compare_lambda_subgrammars_tasks,
	.process = lambda_subgrammars_task_process,
	.dotout = lambda_subgrammars_task_dotout,
	.free = free_lambda_subgrammars_task,
};

