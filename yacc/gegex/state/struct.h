
#ifndef STRUCT_GEGEX_H
#define STRUCT_GEGEX_H

#include <stddef.h>

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
			char* grammar; // arena-owned
			struct gegex* start;
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct gegex** data;
		size_t n, cap;
	} lambda_transitions;
	
	bool reduction_point;
	
	unsigned phase;
};

#endif
