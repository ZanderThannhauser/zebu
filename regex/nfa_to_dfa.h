
struct memory_arena;
struct regex_state;

int regex_nfa_to_dfa(
	struct regex_state** out,
	struct memory_arena* arena,
	struct regex_state*  in);
