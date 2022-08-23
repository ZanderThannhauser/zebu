
#include <stdbool.h>
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
	
	struct lex_state* EOF_transition_to;
	
	struct tokenset* accepting; // freed by tokensetset
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
	
	bool is_freeing;
	
	unsigned phase;
};

