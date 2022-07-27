
struct scope;
struct tokenizer;
struct avl_tree_t;

struct charset* read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
