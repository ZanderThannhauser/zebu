
struct regex_state;
struct memory_arena;

struct regex* regex_from_literal(
	struct memory_arena* arena,
	const char* string,
	size_t len);
