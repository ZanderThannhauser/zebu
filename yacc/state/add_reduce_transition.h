
struct memory_arena;

void yacc_state_add_reduce_transition(
	struct yacc_state* from,
	const struct tokenset* value,
	char* reduce_as,
	unsigned pop_count);
	
