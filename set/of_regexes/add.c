
#include <debug.h>

#include "struct.h"
#include "add.h"

void regexset_add(struct regexset* this, struct regex* ptr)
{
	ENTER;
	
	dpv(ptr);
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; i < n; i++)
	{
		struct regex* ele = this->data[i];
		
		if (ptr < ele)
		{
			this->data[i] = ptr;
			ptr = ele;
		}
		else if (ptr > ele)
		{
			;
		}
		else
		{
			TODO;
		}
	}
	
	this->data[this->n++] = ptr;
	
	EXIT;
}

