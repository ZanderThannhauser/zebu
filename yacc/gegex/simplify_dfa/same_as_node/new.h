struct gegex_same_as_node* new_gegex_same_as_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* state, struct gegextree* set
);
