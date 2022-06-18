
struct memory_arena;
struct regex;

struct regex* regex_clone(
	struct memory_arena* arena,
	struct regex* in);
