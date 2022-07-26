
struct tokensetset;

struct lex_state* dfas_to_dfa(
	struct tokensetset* accepting,
	struct memory_arena* scratchpad,
	struct regexset* starts);
