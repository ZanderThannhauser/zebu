
#include "../struct.h"

struct setup_trie_task
{
	struct task super;
	
	struct gegex* node;
	
	const char* name;
	
	char* built_name;
	
	struct memory_arena* scratchpad;
};

