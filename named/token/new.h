
struct memory_arena;
struct regex;

struct named_token* new_named_token(
	struct memory_arena* arena,
	char* name,
	struct regex* token);
