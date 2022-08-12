
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void strset_foreach(struct strset* this, void (*runme)(const char* str))
{
	unsigned i, n;
	for (i = 0, n = this->n; i < n; i++)
		runme(this->data[i]);
}

