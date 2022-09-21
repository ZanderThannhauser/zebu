
#include <stdbool.h>

struct gegex
{
	struct {
		struct gegex_transition** data;
		unsigned n, cap;
	} transitions;
	
	struct {
		struct gegex** data;
		unsigned n, cap;
	} lambdas;
	
	struct {
		struct gegex_grammar_transition** data;
		unsigned n, cap;
	} grammars;
	
	bool accepts;
};

