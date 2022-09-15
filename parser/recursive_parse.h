
struct pragma_once;
struct options;
struct scope;
struct lex;

void recursive_parse(
	struct pragma_once* pragma_once,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd,
	int fd);
