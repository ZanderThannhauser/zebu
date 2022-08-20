
struct lex;
struct options;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;
struct scope;

void recursive_parse(
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	struct memory_arena* scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	int fd,
	struct lex* lex);
