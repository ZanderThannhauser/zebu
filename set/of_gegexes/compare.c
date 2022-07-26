
#include <debug.h>

#include <macros/min.h>

#include "struct.h"
#include "compare.h"

int compare_gegexsets(
	const struct gegexset* this,
	const struct gegexset* them)
{
	int cmp = 0;
	ENTER;
	
	for (unsigned i = 0, n = min(this->n, them->n); !cmp && i < n; i++)
	{
		struct gegex* a = this->data[i], *b = them->data[i];
		
		if (a > b)
			cmp = +1;
		else if (a < b)
			cmp = -1;
	}
	
	if (!cmp)
	{
		unsigned a_n = this->n, b_n = them->n;
		if (a_n > b_n)
			cmp = +1;
		else if (a_n < b_n)
			cmp = -1;
	}
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

