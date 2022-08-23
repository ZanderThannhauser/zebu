
struct tokenizer;
struct avl_tree_t;
struct scope;

struct charset* read_symdiff_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope);
