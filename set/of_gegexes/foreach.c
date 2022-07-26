
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void gegexset_foreach(
	const struct gegexset* this,
	void (*runme)(struct gegex* state))
{
	ENTER;
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	EXIT;
}

