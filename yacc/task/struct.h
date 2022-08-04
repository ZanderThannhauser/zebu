
#include "kind.h"

struct task_inheritance;

struct task
{
	enum task_kind kind;
	
	struct task_inheritance* inheritance;
};

