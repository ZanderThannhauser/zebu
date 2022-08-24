struct gegex* gegex_nfa_to_dfa_helper(
	#ifdef VERBOSE
	unsigned *node_count,
	#endif
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* states,
	struct avl_tree_t* mappings
);
