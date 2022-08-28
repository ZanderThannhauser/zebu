
#include <stdlib.h>

#include <debug.h>

#include "transition/new.h"

#include "struct.h"
#include "add_transition.h"

void regex_add_transition(
	struct regex* from,
	unsigned value,
	struct regex* to
) {
	ENTER;
	
	avl_insert(from->transitions, new_regex_transition(value, to));
	
	EXIT;
}


















