
struct options;
struct scope;
struct memory_arena;
struct tokenizer;
struct avl_tree_t;
struct name;

void read_grammar(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
