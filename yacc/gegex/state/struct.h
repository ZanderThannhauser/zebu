
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
			char* grammar; // will arena-free
			struct gegex* start;
			struct gegex* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct rtransition {
			unsigned token;
			char* reduce_as; // will arena-free
		}** data;
		size_t n, cap;
	} reduction_transitions;
	
	struct {
		struct gegex** data;
		size_t n, cap;
	} lambda_transitions;
	
	unsigned phase;
};

#endif
