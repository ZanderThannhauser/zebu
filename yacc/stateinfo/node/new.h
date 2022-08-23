
struct gegex;
struct tokenset;

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads);
