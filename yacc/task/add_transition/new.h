
struct yacc_state;
struct yacc_stateinfo;

struct add_transition_task* new_add_transition_task(
	struct memory_arena* arena,
	struct yacc_state** write_to_me,
	struct yacc_stateinfo* stateinfo);
