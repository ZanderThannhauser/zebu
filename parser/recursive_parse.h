
void recursive_parse(
	struct pragma_once* pragma_once,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd,
	int fd);
