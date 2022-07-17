
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void set_foreach(struct set* this, void (*runme)(const void* str))
{
	ENTER;
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
	EXIT;
}

