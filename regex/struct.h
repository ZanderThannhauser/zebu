
#include <stdbool.h>

#include <enums/token_kind.h>

struct regex
{
	struct regex* transitions[256];
	
	struct {
		struct regex** data;
		unsigned n, cap;
	} lambdas;
	
	struct regex* EOF_transition_to;
	
	unsigned accepts;
	
	enum token_kind kind;
};

