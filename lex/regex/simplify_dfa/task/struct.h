
#include "../pair/struct.h"

struct regex_simplify_task
{
	struct regex_pair pair;
	
	unsigned hopcount;
	
	struct memory_arena* arena;
};

