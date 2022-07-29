
struct tokenset;
struct memory_arena;
struct yacc_state;

void yacc_state_add_transition(
	struct yacc_state* this,
	struct memory_arena* arena,
	const struct tokenset* value,
	struct yacc_state* to);
