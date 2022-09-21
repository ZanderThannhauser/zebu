
#include <stdlib.h>
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void gegex_add_lambda_transition(
	struct gegex* from,
	struct gegex* to)
{
	ENTER;
	
	dpv(from);
	dpv(to);
	
	if (from->lambdas.n + 1 > from->lambdas.cap)
	{
		from->lambdas.cap = from->lambdas.cap * 2 ?: 1;
		
		dpv(from->lambdas.cap);
		
		from->lambdas.data = srealloc(from->lambdas.data, sizeof(*from->lambdas.data) * from->lambdas.cap);
	}
	
	from->lambdas.data[from->lambdas.n++] = to;
	
	EXIT;
}















