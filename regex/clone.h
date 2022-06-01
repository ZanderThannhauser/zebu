
struct memory_arena;
struct regex_state;

int regex_clone(
	struct regex_state** out,
	struct memory_arena* arena,
	struct regex_state* in);

