
struct regex_state;
struct memory_arena;

int regex_lambda_all_accepting_states(
	struct regex_state* regex,
	struct memory_arena* arena,
	struct regex_state* dest,
	bool keep_accepting);
