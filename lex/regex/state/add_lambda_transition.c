
#include <stdlib.h>

#include <debug.h>

#include <set/regex/add.h>

#include "struct.h"
#include "add_lambda_transition.h"

void regex_add_lambda_transition(
	struct regex* from,
	struct regex* to)
{
	ENTER;
	
	regexset_add(from->lambda_transitions, to);
	
	EXIT;
}
















