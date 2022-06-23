
struct charset;
struct memory_arena;

struct regex* regex_from_charset(
	struct charset* charset,
	struct memory_arena* arena);
