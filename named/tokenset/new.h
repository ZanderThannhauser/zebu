
struct tokenset;
struct memory_arena;

struct named_tokenset* new_named_tokenset(
	struct memory_arena* arena,
	const char* name, struct tokenset* tokenset);
