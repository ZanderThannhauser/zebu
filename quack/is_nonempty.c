
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool quack_is_nonempty(const struct quack* this)
{
	return !!this->n;
}

