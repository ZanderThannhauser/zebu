
#include <stddef.h>
#include <stdbool.h>

struct regex
{
	struct avl_tree_t* transitions; // struct regex_transition*
	
	struct regexset* lambda_transitions;
	
	struct regex* default_transition_to;
	
	struct regex* EOF_transition_to;
	
	unsigned phase;
	
	unsigned is_accepting, priority;
};

