
struct regex_state;
struct tokenizer;
struct memory_arena;

int read_prefixes_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer);
