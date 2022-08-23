
struct percolate_lookaheads_task* new_percolate_lookaheads_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct gegex* state,
	struct lookahead_deps* ldeps);
