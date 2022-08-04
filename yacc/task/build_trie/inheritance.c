
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance build_trie_task_inheritance = {
	.compare = compare_build_trie_tasks,
	.process = build_trie_task_process,
	#ifdef DEBUGGING
	.dotout = build_trie_task_dotout,
	#endif
	.free = free_build_trie_task,
};

