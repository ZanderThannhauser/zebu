
#include "../struct.h"

struct refcount_task
{
	struct task super;
	
	struct gegex* start, *node;
};

