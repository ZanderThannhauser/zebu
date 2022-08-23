
struct memory_arena;
struct tokenizer;
struct avl_tree_t;
struct scope;

struct charset* read_root_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope);
