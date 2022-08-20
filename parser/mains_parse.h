
struct options;
struct memory_arena;
struct lex;
struct scope;

void mains_parse(
	struct options* options,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad,
	struct lex* lex,
	const char* path);
