
struct tokenizer;
struct avl_tree_t;
struct scope;

struct charset* read_intersect_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
