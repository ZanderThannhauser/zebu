
void lex_simplify_dfa_add_dep(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* dependent_of,
	struct lex_state* a_on, struct lex_state* b_on,
	struct lex_state* a_of, struct lex_state* b_of);
