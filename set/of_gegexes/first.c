
#include <stddef.h>

#include <debug.h>

#include "struct.h"
#include "first.h"

struct gegex* gegexset_first(
	const struct gegexset* this,
	bool (*runme)(struct gegex* state, va_list*), ...)
{
	struct gegex* ele;
	va_list ap;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		va_start(ap, runme);
		
		if (runme(ele = this->data[i], &ap))
		{
			va_end(ap);
			return ele;
		}
		
		va_end(ap);
	}
	
	return NULL;
}

