
struct regex_state;
struct tokenizer;
struct memory_arena;

int read_root_token_expression(
	struct regex_state** out,
	struct memory_arena* token_scratchpad,
	struct tokenizer* tokenizer);
