
struct lex;
struct tokenizer;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;
struct options;

void read_directive(
	struct tokenizer* tokenizer,
	struct avl_tree_t* grammar,
	struct options* options,
	struct avl_tree_t* fragments,
	struct pragma_once* pragma_once,
	struct memory_arena* token_scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex);
