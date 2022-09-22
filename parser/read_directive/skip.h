
struct pragma_once;
struct tokenizer;
struct options;
struct scope;
struct lex;

void read_skip_directive(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
