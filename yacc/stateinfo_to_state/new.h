
struct stateinfo_to_state* new_stateinfo_to_state(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct yacc_state* state);
