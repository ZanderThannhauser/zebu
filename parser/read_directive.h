
struct scope;
struct lex;
struct tokenizer;
struct avl_tree_t;
struct pragma_once;
struct memory_arena;
struct options;

void read_directive(
	#ifdef WITH_ARENAS
	struct memory_arena* parser_arena,
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex);
