
struct tokenizer;
struct avl_tree_t;
struct scope;

struct charset* read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
