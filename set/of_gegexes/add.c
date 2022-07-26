
#include <debug.h>

#include "struct.h"
#include "add.h"

void gegexset_add(struct gegexset* this, struct gegex* ptr)
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
		struct gegex* ele = this->data[i];
		
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

