
struct pragma_once;
struct options;
struct scope;
struct lex;
struct avl_tree_t;

void recursive_parse(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd,
	int fd);
