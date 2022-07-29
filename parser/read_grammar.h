
struct scope;
struct memory_arena;
struct tokenizer;
struct avl_tree_t;
struct name;

void read_grammar(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
