
#include "../struct.h"

struct explore_lookaheads_task
{
	struct task super;
	
	struct gegex* start;
	
	const char* name;
	struct gegex* node;
	const char* invocation;
	
	struct memory_arena* scratchpad;
};

