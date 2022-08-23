
void simplify_dfa_dotout(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regextree* universe,
	struct avl_tree_t* connections,
	unsigned hopcount);
