
struct tokenizer;
struct avl_tree_t;

struct charset* read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
