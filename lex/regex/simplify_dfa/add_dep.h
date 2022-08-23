
void simplify_dfa_add_dep(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* dependent_of,
	struct regex* a_on, struct regex* b_on,
	struct regex* a_of, struct regex* b_of);
