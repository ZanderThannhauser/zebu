
#include <debug.h>

#include "struct.h"
#include "all.h"

bool gegexset_all(
	const struct gegexset* this,
	bool (*runme)(struct gegex* state))
{
	bool value = true;
	for (unsigned i = 0, n = this->n; value && i < n; i++)
		value = runme(this->data[i]);
	return value;
}

