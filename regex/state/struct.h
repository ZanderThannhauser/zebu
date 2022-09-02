
struct regex
{
	struct {
		struct regex_transition {
			unsigned char value;
			struct regex* to;
		}** data;
		unsigned n, cap;
	} transitions;
	
	struct {
		struct regex** data;
		size_t n, cap;
	} lambda_transitions;
	
	struct {
		struct regex* to;
		struct unsignedcharset* exceptions;
	} default_transition;
	
	struct regex* EOF_transition_to;
	
	unsigned is_accepting;
	
	bool is_literal;
};

