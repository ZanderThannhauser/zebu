
struct regex_state
{
	bool is_accepting;
	
	struct {
		struct transition {
			char value;
			struct regex_state* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct regex_state** data;
		size_t n, cap;
	} lambda_transitions;
	
	struct regex_state* default_transition_to;
	
	unsigned phase;
};

