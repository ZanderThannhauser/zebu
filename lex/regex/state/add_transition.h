
struct memory_arena;
struct regex;

void regex_add_transition(
	struct regex* from,
	unsigned value,
	struct regex* to);
