
#include <stddef.h>
#include <stdbool.h>

struct tokenset;

struct regex
{
	struct {
		struct transition {
			unsigned char value; // must be the first
			struct regex* to;
		}** data;
		size_t n, cap;
	} transitions;
	
	struct {
		struct regex** data;
		size_t n, cap;
	} lambda_transitions;
	
	struct regex* default_transition_to;
	
	struct regex* EOF_transition_to;
	
	struct memory_arena* arena;
	
	unsigned phase;
	
	#ifdef DEBUGGING
	unsigned dotout_phase;
	#endif
	
	unsigned is_accepting, priority;
	
	bool is_freeing;
};

