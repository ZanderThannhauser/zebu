
struct regex* regex_simplify_dfa_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* connections,
	struct regex* original_start);
