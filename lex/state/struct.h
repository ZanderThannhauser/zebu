
#include <enums/token_kind.h>

struct lex_state
{
	struct lex_state* transitions[256];
	
	struct lex_state* EOF_transition_to;
	
	struct unsignedset* accepts; // free me
	
	enum token_kind kind;
};

