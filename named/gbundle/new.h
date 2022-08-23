
struct memory_arena;
struct gegex;

struct named_gbundle* new_named_gbundle(
	struct memory_arena* arena,
	char* name,
	struct gegex* start,
	struct gegex* end);
