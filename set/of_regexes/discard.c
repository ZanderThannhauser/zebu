
#include <stdbool.h>

#include <debug.h>

#include "struct.h"
#include "discard.h"

void regexset_discard(
	struct regexset* this,
	struct regex* state)
{
	bool found = false;
	unsigned i, n;
	ENTER;
	
	for (i = 0, n = this->n; i < n; i++)
	{
		struct regex* ele = this->data[i];
		
		if (found)
		{
			this->data[i - 1] = ele;
		}
		else if (state == ele)
		{
			found = true;
		}
	}
	
	if (found)
		this->n--;
	
	EXIT;
}

