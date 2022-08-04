
#include "../struct.h"

struct refcount_task
{
	struct task super;
	
	struct memory_arena* scratchpad;
	
	struct gegex* start, *node;
};

