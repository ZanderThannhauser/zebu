
struct scope;
struct lex;
struct tokenizer;
struct memory_arena;
struct avl_tree_t;
struct name;

void read_fragment(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip);
