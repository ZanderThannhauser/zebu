
struct lex;
struct tokenizer;
struct memory_arena;

void read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* token_scratchpad,
	struct lex* lex);
