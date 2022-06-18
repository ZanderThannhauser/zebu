
struct lex;
struct options;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;

void recursive_parse(
	struct avl_tree_t* grammar,
	struct options* options,
	struct avl_tree_t* fragments,
	struct pragma_once* pragma_once,
	struct memory_arena* token_scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	char* path,
	struct lex* lex);
