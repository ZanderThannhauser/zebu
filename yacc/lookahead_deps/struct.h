
struct lookahead_deps
{
	struct avl_tree_t *dependant_of, *dependant_on; // gegex -> gegex
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

