
struct lex_state* dfas_to_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokensetset* accepting,
	struct regexset* starts);
