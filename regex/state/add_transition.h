
struct memory_arena;
struct regex;

void regex_add_transition(
	struct regex* from,
	struct memory_arena* arena,
	unsigned value,
	struct regex* to);
