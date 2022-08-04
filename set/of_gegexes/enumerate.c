
#include <debug.h>

#include "struct.h"
#include "enumerate.h"

void gegexset_enumerate(
	const struct gegexset* this,
	void (*runme)(unsigned, struct gegex*))
{
	ENTER;
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		runme(i, this->data[i]);
	}
	EXIT;
}

