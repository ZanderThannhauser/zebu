
#include "../struct.h"

struct add_reductions_task
{
	struct task super;
	
	const char* name;
	
	struct gegex* node;
	
	struct memory_arena* scratchpad;
};

