
struct memory_arena;
struct regex;

struct regex* regex_one_or_more(
	struct memory_arena* arena,
	struct regex* in);
