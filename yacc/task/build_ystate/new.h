
struct build_ystate_task* new_build_ystate_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_state* state,
	struct yacc_stateinfo* stateinfo);
