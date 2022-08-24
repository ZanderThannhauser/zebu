
#include "process.h"
#include "dotout.h"
#include "compare.h"
#include "free.h"
#include "inheritance.h"

struct task_inheritance setup_trie_task_inheritance = {
	.compare = compare_setup_trie_tasks,
	.process = setup_trie_task_process,
	#ifdef DOTOUT
	.dotout = setup_trie_task_dotout,
	#endif
	.free = free_setup_trie_task,
};

