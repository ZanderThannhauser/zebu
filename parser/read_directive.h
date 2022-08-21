
struct scope;
struct lex;
struct tokenizer;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;
struct options;

void read_directive(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex);
