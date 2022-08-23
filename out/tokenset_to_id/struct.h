
#include <stdbool.h>

struct tokenset_to_id_node
{
	bool is_tokenset;
	union
	{
		const struct tokenset* tokenset;
		const char* grammar;
	};
	unsigned id;
};

struct tokenset_to_id
{
	struct avl_tree_t* tree;
	struct tokenset* eof;
	unsigned next;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};
