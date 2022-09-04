
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
	
	struct {
		struct unsignedcharset* exceptions;
		struct lex_state* to;
	} default_transition;
	
	struct lex_state* EOF_transition_to;
	
	struct unsignedset* accepts; // free me
};

