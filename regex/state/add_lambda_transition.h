
struct regex_state;
struct memory_arena;

int regex_state_add_lambda_transition(
	struct regex_state* from,
	struct memory_arena* arena,
	struct regex_state* to);
