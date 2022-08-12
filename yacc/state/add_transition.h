
struct tokenset;
struct memory_arena;
struct yacc_state;

struct ytransition* yacc_state_add_transition(
	struct yacc_state* from,
	struct memory_arena* arena,
	const struct tokenset* value,
	struct yacc_state* to);
