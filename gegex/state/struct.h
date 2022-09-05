
#ifndef STRUCT_GEGEX_H
#define STRUCT_GEGEX_H

#include <stddef.h>
#include <stdbool.h>

struct gegex
{
	struct {
		struct gegex_transition {
			unsigned token;
			struct stringset* tags; // owned, might be NULL
			struct gegex* to;
		}** data;
		unsigned n, cap;
	} transitions;
	
	struct {
		struct gegex_grammar_transition {
			struct string* grammar;
			struct stringset* tags; // owned, might be NULL
			struct gegex* to;
		}** data;
		unsigned n, cap;
	} grammar_transitions;
	
	struct {
		struct gegex** data; // owned
		unsigned n, cap;
	} lambda_transitions;
	
	bool is_reduction_point;
};

#endif
