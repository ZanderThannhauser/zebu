
struct lex_state;
struct ptrset;

struct unsignedsetset* dfas_to_dfa(
	struct lex_state** outgoing,
	struct ptrset* starts);
