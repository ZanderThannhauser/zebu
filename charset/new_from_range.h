
struct charset* new_charset_from_range(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char low, char high);
