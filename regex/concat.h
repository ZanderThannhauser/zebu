
struct memory_arena;
struct regex;

void regex_concat(
	struct memory_arena* arena,
	struct regex* left,
	struct regex* right);
