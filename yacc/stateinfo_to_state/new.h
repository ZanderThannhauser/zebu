
struct memory_arena;

struct stateinfo_to_state* new_stateinfo_to_state(
	struct memory_arena* arena,
	struct yacc_stateinfo* stateinfo,
	struct yacc_state* state);
