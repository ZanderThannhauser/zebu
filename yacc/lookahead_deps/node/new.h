
struct lookahead_deps_node* new_lookahead_deps_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* a,
	struct gegex* b);
