
struct memory_arena;
struct tokenizer;
struct avl_tree_t;

void read_grammar(
	struct tokenizer* tokenizer,
	struct avl_tree_t* grammar,
	struct avl_tree_t* fragments,
	struct memory_arena* scratchpad);
