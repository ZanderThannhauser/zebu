
struct memory_arena;
struct regex_state;

int regex_state_add_transition(
	struct regex_state* state,
	struct memory_arena* arena,
	char value,
	struct regex_state* to);
