
#include <stdbool.h>

struct regex
{
	struct regex* transitions[256];
	
	struct {
		struct regex** data;
		unsigned n, cap;
	} lambda_transitions;
	
	struct regex* EOF_transition_to;
	
	unsigned is_accepting;
	
	enum token_kind token_kind;
};

