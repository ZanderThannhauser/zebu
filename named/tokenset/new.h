
struct tokenset;

struct named_tokenset* new_named_tokenset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name, struct tokenset* tokenset);
