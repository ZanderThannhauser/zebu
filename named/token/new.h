
struct regex;

struct named_token* new_named_token(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct regex* token);
