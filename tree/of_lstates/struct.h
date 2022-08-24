
struct lstatetree
{
	struct avl_tree_t* tree;
	unsigned n;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

