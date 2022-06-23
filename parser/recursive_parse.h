
struct lex;
struct options;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;

void recursive_parse(
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	struct memory_arena* scratchpad,
	int absolute_dirfd,
	int old_relative_dirfd,
	char* path,
	struct lex* lex);
