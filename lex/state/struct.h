
#include <stddef.h>

struct lex_state
{
	struct {
		struct ltransition {
			unsigned char value;
			struct lex_state* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct lex_state* default_transition_to;
	
	unsigned phase;
	
	struct tokenset* accepting; // freed by tokensetset
};

