
#ifndef STRUCT_GEGEX_H
#define STRUCT_GEGEX_H

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
			const char* grammar;
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct gegex** data;
		size_t n, cap;
	} lambda_transitions;
	
	unsigned phase;
	
	char* reduce_to;
	
	bool is_freeing;
};

#endif
