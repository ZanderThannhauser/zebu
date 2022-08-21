
struct options;
struct memory_arena;
struct lex;
struct scope;

void mains_parse(
	struct memory_arena* token_arena,
	struct memory_arena* grammar_arena,
	struct options* options,
	struct avl_tree_t* grammar,
	struct lex* lex,
	const char* path);
