
void gegex_simplify_dfa_add_dep(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* dependent_of,
	struct gegex* a_on, struct gegex* b_on,
	struct gegex* a_of, struct gegex* b_of);
