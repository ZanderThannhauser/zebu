
struct regex_state;
struct memory_arena;

int regex_from_literal(
	struct regex_state** out,
	struct memory_arena* arena,
	const char* string,
	size_t len);
