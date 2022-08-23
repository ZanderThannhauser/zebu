
struct charset;

struct regex* regex_from_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct charset* charset);
