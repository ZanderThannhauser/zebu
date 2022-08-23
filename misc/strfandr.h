
char* strfandr(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* original,
	const char* findme,
	const char* replacewith);
