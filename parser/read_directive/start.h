
struct pragma_once;
struct tokenizer;
struct options;
struct scope;
struct lex;

void read_start_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd);
