
#include "../struct.h"

struct build_trie_task
{
	struct task super;
	
	struct memory_arena* scratchpad;
	
	const char* name;
	
	struct gegex* start;
	
	struct gegex* mirrorme;
	
	struct gegex* building;
	
	unsigned popcount;
};
