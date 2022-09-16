
#include <stdbool.h>

#include <enums/token_kind.h>

struct regex
{
	struct regex* transitions[256];
	
	struct {
		struct regex** data;
		unsigned n, cap;
	} lambda_transitions;
	
	struct regex* EOF_transition_to;
	
	unsigned is_accepting;
	
	enum token_kind kind;
};

