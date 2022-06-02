
struct regex_state;
struct tokenizer;
struct memory_arena;

int read_concat_token_expression(
	bool* is_nfa_out,
	struct regex_state** out,
	struct memory_arena* scratchpad,
	struct tokenizer* tokenizer);
