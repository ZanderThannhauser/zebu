
struct regex;

struct memory_arena;

void regex_complement(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* start);
