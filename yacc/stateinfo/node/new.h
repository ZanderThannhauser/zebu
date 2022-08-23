
struct gegex;
struct tokenset;
struct memory_arena;

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	struct memory_arena* arena,
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads);
