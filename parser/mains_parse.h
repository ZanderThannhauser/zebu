
struct options;
struct memory_arena;
struct lex;
struct scope;
void mains_parse(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct options* options,
	struct avl_tree_t* grammar,
	struct lex* lex,
	const char* path
);
