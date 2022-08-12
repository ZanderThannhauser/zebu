
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void regexset_foreach(
	const struct regexset* this,
	void (*runme)(struct regex* state))
{
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
}

