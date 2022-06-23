
struct regex;
struct memory_arena;

struct regex* regex_intersect_dfas(
	struct regex* A,
	struct regex* B,
	struct memory_arena* arena);
