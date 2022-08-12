
struct yacc_shared* new_yacc_shared(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad,
	unsigned EOF_token_id);
