
struct pragma_once;
struct tokenizer;
struct options;
struct scope;
struct lex;

void read_start_directive(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
