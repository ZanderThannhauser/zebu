
#include <avl/tree_t.h>

struct pragma_once
{
	struct avl_tree_t* tree;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

