

struct yacc_shared* new_yacc_shared(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	struct memory_arena* tokenizer_arena,
	struct memory_arena* parser_arena,
	#endif
	struct lex* lex,
	struct avl_tree_t* grammar,
	unsigned EOF_token_id);
