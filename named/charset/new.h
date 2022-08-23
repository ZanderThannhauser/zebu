
struct charset;

struct named_charset* new_named_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct charset* charset);
