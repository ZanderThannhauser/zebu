
struct avl_tree_t;
struct lex;

int mains_parse(
	struct avl_tree_t* grammar,
	const char* path,
	struct lex* lex);
