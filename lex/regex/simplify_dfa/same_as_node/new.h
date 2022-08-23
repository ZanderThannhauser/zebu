
struct same_as_node* new_same_as_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* state, struct regextree* set);
