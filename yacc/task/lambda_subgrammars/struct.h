
#include "../struct.h"

struct lambda_subgrammars_task
{
	struct task super;
	
	struct gegex* start;
	
	struct gegex* node;
	
	struct memory_arena* scratchpad;
};

