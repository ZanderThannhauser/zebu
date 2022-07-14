
#include "../struct.h"

struct add_reductions_task
{
	struct task super;
	
	const char* name;
	
	struct gegex* end;
	
	struct memory_arena* scratchpad;
};

