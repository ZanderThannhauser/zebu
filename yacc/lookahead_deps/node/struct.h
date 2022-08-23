
struct lookahead_deps_node
{
	struct gegex* a; // must be first
	struct gegexset* b;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};
