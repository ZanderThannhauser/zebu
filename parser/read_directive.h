
struct avl_tree_t;
struct pragma_once;
struct tokenizer;
struct options;
struct scope;
struct lex;

void read_directive(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	const char* root_path,
	const char* curr_path);
