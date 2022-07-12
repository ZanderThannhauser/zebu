
#ifdef DEBUGGING
#include <debug.h>

#include "struct.h"
#include "print.h"

void tokenset_print(struct tokenset* this)
{
	ENTER;
	
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
	{
		ddprintf("[%u] = %u\n", i, this->data[i]);
	}
	EXIT;
}

#endif
