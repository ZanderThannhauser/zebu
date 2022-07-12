
#include <debug.h>

#include "struct.h"
#include "update.h"

bool tokenset_update(struct tokenset* this, struct tokenset* them)
{
	bool changed = false;
	ENTER;
	
	unsigned i = 0, n = this->n;
	unsigned j = 0, m = them->n;
	
	while (i < n && j < m)
	{
		unsigned a = this->data[i], b = them->data[j];
		
		dpv(a);
		dpv(b);
		
		if (a < b)
		{
			i++;
		}
		else if (b < a)
		{
			TODO;
		}
		else
		{
			TODO;
		}
	}
	
	while (j < m)
	{
		unsigned b = them->data[j++];
		
		dpv(b);
		
		if (this->n + 1 > this->cap)
		{
			this->cap = this->cap << 1 ?: 1;
			this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
		}
		
		this->data[this->n++] = b;
		
		changed = true;
	}
	
	dpvb(changed);
	
	EXIT;
	return changed;
}













