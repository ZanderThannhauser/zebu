
struct yacc_state
{
	struct lex_state* tokenizer_start;
	
	struct {
		struct yacc_state_transition {
			struct unsignedset* on;
			struct yacc_state* to;
		}** data;
		unsigned n, cap;
	} transitions;
	
	struct {
		struct yacc_state_grammar_transition {
			struct string* grammar;
			struct yacc_state* to;
		}** data;
		unsigned n, cap;
	} grammar_transitions;
	
	struct {
		struct yacc_state_reduce_transition {
			struct unsignedset* on;
			
			struct string* reduce_as;
			struct string* grammar;
			
			struct reductioninfo* reductioninfo;
			
			struct structinfo* structinfo;
		}** data;
		unsigned n, cap;
	} reduce_transitions;
};

