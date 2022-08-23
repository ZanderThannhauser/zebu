
struct regex_state;
struct memory_arena;

struct regex* regex_from_literal(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* string,
	size_t len);
