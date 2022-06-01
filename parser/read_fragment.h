
struct lex;
struct tokenizer;
struct memory_arena;

int read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* token_scratchpad,
	struct lex* lex);
