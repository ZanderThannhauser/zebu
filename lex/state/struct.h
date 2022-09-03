
#include <stdbool.h>
#include <stddef.h>

struct lex_state
{
	struct {
		struct lex_transition {
			unsigned char value;
			struct lex_state* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct lex_state* default_transition_to;
	
	struct lex_state* EOF_transition_to;
	
	struct unsignedset* accepts; // free me
};

