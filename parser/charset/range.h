
struct scope;
struct tokenizer;
struct avl_tree_t;

struct charset* read_range_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope);
