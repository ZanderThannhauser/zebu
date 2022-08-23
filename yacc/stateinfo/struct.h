
struct yacc_stateinfo
{
	struct avl_tree_t* tree;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};
