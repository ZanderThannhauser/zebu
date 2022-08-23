
void gegex_simplify_dfa_dotout(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* universe,
	struct avl_tree_t* connections,
	unsigned hopcount);
