
struct avl_tree_t;
struct lex;

int yacc(
	void** out,
	struct avl_tree_t* grammar,
	struct lex* lex,
	bool verbose);
