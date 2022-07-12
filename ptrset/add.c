
#include <debug.h>

#include "struct.h"
#include "add.h"

void ptrset_add(struct ptrset* this, const void* ptr)
{
	ENTER;
	
	dpv(ptr);
	
	TODO;
	#if 0
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	unsigned i, n;
	
	for (i = 0, n = this->n; i < n; i++)
	{
		dpvs(str);
		dpvs(this->data[i]);
		
		int cmp = strcmp(str, this->data[i]);
		
		if (cmp < 0)
		{
			const char* temp = this->data[i];
			this->data[i] = str;
			str = temp;
		}
		else if (cmp > 0)
		{
			i++;
		}
		else
		{
			TODO;
		}
	}
	
	this->data[this->n++] = str;
	#endif
	
	EXIT;
}

