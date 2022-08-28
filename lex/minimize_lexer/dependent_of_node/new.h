
struct lex_dependent_of_node* new_lex_dependent_of_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* a, struct lex_state* b);
