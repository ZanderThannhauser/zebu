
struct lookahead_deps;

struct expand_tree_task* new_expand_tree_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct lookahead_deps* ldeps,
	struct gegex* state,
	const char* reduce_as,
	struct tokenset* lookaheads);
