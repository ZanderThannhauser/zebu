
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void tokensetset_foreach(
	const struct tokensetset* this,
	void (*runme)(struct tokenset* ele))
{
	ENTER;
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	EXIT;
}

