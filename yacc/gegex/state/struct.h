
#ifndef STRUCT_GEGEX_H
#define STRUCT_GEGEX_H

#include <stddef.h>
#include <stdbool.h>

struct gegex
{
	struct {
		struct transition {
			unsigned token;
			struct gegex* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct gtransition {
			char* grammar; // owned
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct gegex** data;
		size_t n, cap;
	} lambda_transitions;
	
	bool is_reduction_point;
	
	unsigned popcount;
	unsigned phase, refcount;
};

#endif
