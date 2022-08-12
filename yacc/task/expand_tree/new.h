
struct expand_tree_task* new_expand_tree_task(
	struct yacc_stateinfo* stateinfo,
	struct lookahead_deps* ldeps,
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads);
