
#include <stdlib.h>

#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void regex_add_lambda_transition(
	struct regex* from,
	struct regex* to)
{
	ENTER;
	
	if (from->lambdas.n + 1 >= from->lambdas.cap)
	{
		from->lambdas.cap = from->lambdas.cap * 2 ?: 1;
		
		from->lambdas.data = srealloc(from->lambdas.data, sizeof(*from->lambdas.data) * from->lambdas.cap);
	}
	
	from->lambdas.data[from->lambdas.n++] = to;

	EXIT;
}
















