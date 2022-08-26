
#include "../pair/struct.h"

struct lex_simplify_task
{
	struct lex_pair pair;
	
	unsigned hopcount;
	
	struct memory_arena* arena;
};

