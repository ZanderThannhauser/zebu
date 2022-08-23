
struct pragma_once;

void recursive_parse(
	#ifdef WITH_ARENAS
	struct memory_arena* parser_arena,
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	int absolute_dirfd,
	int relative_dirfd,
	int fd,
	struct lex* lex);
