
char* scope_build_absolute_name(
	struct scope* this,
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* suffix,
	size_t suffix_strlen);
