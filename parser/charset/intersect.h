
struct tokenizer;
struct avl_tree_t;
struct scope;
struct memory_arena;

struct charset* read_intersect_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope);
