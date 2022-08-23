
struct lex_state* dfas_to_dfa(
	struct memory_arena* arena,
	struct tokensetset* accepting,
	struct regexset* starts);
