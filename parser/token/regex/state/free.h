
struct regex;
struct memory_arena;

void free_regex(
	struct regex* this,
	struct memory_arena* arena);
