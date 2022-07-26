
#include <stddef.h>
#include <stdbool.h>

struct tokenset;

struct regex
{
	struct {
		struct transition {
			unsigned char value;
			struct regex* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct regex** data;
		size_t n, cap;
	} lambda_transitions;
	
	struct regex* default_transition_to;
	
	unsigned phase;
	
	unsigned is_accepting;
	
	bool is_freeing;
};

