
#include "../pair/struct.h"

struct simplify_task
{
	struct pair pair;
	
	unsigned hopcount;
	
	struct memory_arena* arena;
};

