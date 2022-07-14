
#include "../struct.h"

struct explore_lookaheads_task
{
	struct task super;
	
	const char* name;
	struct gegex* node;
	const char* invocation;
	struct gegex* end;
	
	struct memory_arena* scratchpad;
};

