
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
	
	struct regex* default_transition_to;
	
	struct regex* EOF_transition_to;
	
	unsigned phase;
	
	unsigned is_accepting, priority;
};

