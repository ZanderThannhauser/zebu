
struct options;
struct scope;
struct memory_arena;
struct tokenizer;
struct avl_tree_t;
struct name;

void read_grammar(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
