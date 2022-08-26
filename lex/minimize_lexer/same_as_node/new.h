
struct lex_same_as_node* new_lex_same_as_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* state, struct lstatetree* set);
