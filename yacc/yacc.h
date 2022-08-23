
struct yacc_shared;
struct lex;
struct avl_tree_t;
struct memory_arena;

struct yacc_state* yacc(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct memory_arena* tokenizer_arena,
	struct memory_arena* parser_arena,
	struct lex* lex,
	struct avl_tree_t* grammar,
	bool simplify_tokenizer);
