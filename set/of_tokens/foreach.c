
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void tokenset_foreach(
	struct tokenset* this,
	void (*runme)(unsigned token))
{
	for (unsigned i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
}

