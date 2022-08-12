
#include "../struct.h"

struct free_lookahead_deps_task
{
	struct task super;
	
	struct lookahead_deps* ldeps;
};

