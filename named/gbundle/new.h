
struct gegex;

struct named_gbundle* new_named_gbundle(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct gegex* start,
	struct gegex* end);
