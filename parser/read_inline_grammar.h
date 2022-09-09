
struct tokenizer;
struct options;
struct scope;
struct lex;

void read_inline_grammar(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
