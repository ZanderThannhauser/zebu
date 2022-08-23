
struct regex_mapping* new_regex_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regexset* set, struct regex* state);
