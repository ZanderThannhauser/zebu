
#ifndef STRUCT_YACC_STATE
#define STRUCT_YACC_STATE

#include <stddef.h>
#include <stdbool.h>

struct yacc_state
{
	struct {
		struct ytransition {
			const struct tokenset* value; // lex will free
			struct yacc_state* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct rytransition {
			const struct tokenset* value; // lex will free
			char* reduce_as; // arena will free
			unsigned popcount;
		}** data;
		size_t n, cap;
	} reduction_transitions;
	
	struct {
		struct gytransition {
			char* grammar; // arena will free
			struct yacc_state* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
	
	struct lex_state* tokenizer_start;
	
	unsigned phase;
};

#endif
