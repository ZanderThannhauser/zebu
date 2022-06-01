
struct memory_arena;
struct regex_state;

int regex_concat(
	struct memory_arena* arena,
	struct regex_state* left,
	struct regex_state* right);
