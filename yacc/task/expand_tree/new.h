
struct yacc_stateinfo;
struct lookahead_deps;

struct expand_tree_task* new_expand_tree_task(
	struct memory_arena* arena,
	struct yacc_stateinfo* stateinfo,
	struct lookahead_deps* ldeps,
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads);
