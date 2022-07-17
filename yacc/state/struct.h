
#ifndef STRUCT_YACC_STATE
#define STRUCT_YACC_STATE

struct yacc_state
{
	struct {
		struct ytransition {
			unsigned token;
			struct yacc_state* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct gytransition {
			char* grammar; // will arena-free
			struct yacc_state* to;
		}** data;
		size_t n, cap;
	} grammar_transitions;
	
	struct {
		struct rytransition {
			unsigned token;
			char* reduce_as; // will arena-free
		}** data;
		size_t n, cap;
	} reduction_transitions;
	
	struct regex* tokenizer_start;
	
	// unsigned phase;
};

#endif
