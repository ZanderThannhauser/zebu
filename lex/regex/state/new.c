
#include <stdlib.h>

#include <debug.h>

#include <set/regex/new.h>

#include "transition/compare.h"
#include "transition/free.h"
#include "struct.h"
#include "new.h"

struct regex* new_regex(
) {
	ENTER;
	
	struct regex* this = smalloc(sizeof(*this));
	
	this->transitions = avl_alloc_tree(compare_regex_transitions, free_regex_transition);
	
	this->lambda_transitions = new_regexset();
	
	this->default_transition_to = NULL;
	
	this->EOF_transition_to = NULL;
	
	this->phase = 0;
	
	this->is_accepting = 0;
	
	this->priority = 0;
	
	EXIT;
	return this;
}
