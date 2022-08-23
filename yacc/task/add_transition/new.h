
struct yacc_state;

struct add_transition_task* new_add_transition_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_state** write_to_me,
	struct yacc_stateinfo* stateinfo);
