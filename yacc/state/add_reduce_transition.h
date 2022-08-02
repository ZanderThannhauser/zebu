
void yacc_state_add_reduce_transition(
	struct yacc_state* from,
	struct memory_arena* arena,
	const struct tokenset* value,
	const char* reduce_as,
	unsigned pop_count);
	
