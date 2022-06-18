
struct lex;
struct tokenizer;
struct memory_arena;
struct avl_tree_t;

void read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* token_scratchpad,
	struct avl_tree_t* fragments);
