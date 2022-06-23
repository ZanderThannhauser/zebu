
struct memory_arena;
struct regex;

struct regex* regex_simplify_dfa(
	struct regex* original,
	struct memory_arena* arena);
