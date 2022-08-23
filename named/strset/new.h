
struct memory_arena;

struct named_strset* new_named_strset(
	struct memory_arena* arena,
	const char* name, struct strset* strset);
