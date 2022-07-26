
#ifndef STRUCT_YACC_STATE
#define STRUCT_YACC_STATE

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
			const char* reduce_as; // arena will free
		}** data;
		size_t n, cap;
	} reduction_transitions;
	
	struct {
		struct gytransition {
			const char* grammar; // arena will free
			struct yacc_state* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct lex_state* tokenizer_start;
	
	unsigned phase;
};

#endif
