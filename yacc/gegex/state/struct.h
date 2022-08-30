
#ifndef STRUCT_GEGEX_H
#define STRUCT_GEGEX_H

#include <stddef.h>
#include <stdbool.h>

struct gegex
{
	struct {
		struct gegex_transition {
			unsigned token;
			struct stringset* tags; // owned
			struct gegex* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct gegex_grammar_transition {
			char* grammar; // owned
			struct stringset* tags; // owned
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct gegex** data; // owned
		size_t n, cap;
	} lambda_transitions;
	
	bool is_reduction_point;
	
	unsigned popcount;
	unsigned phase, refcount;
};

#endif
