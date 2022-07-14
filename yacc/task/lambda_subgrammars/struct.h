
#include "../struct.h"

struct lambda_subgrammars_task
{
	struct task super;
	
	const char* name;
	
	struct gegex* node;
	
	struct memory_arena* scratchpad;
};

