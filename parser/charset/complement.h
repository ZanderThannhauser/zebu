
struct scope;
struct tokenizer;
struct avl_tree_t;
struct memory_arena;

struct charset* read_complement_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope);
