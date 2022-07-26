
#include <debug.h>

#include "struct.h"
#include "update.h"

bool tokensetset_update(struct tokensetset* this, struct tokensetset* them)
{
	bool changed = false;
	ENTER;
	
	unsigned i = 0, n = this->n;
	unsigned j = 0, m = them->n;
	
	TODO;
	#if 0
	while (i < n && j < m)
	{
		const char* a = this->data[i], *b = them->data[j];
		
		dpvs(a);
		dpvs(b);
		
		int cmp = strcmp(a, b);
		if (cmp < 0)
		{
			TODO;
		}
		else if (cmp > 0)
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
		const char* b = them->data[j++];
		
		dpvs(b);
		
		if (this->n + 1 > this->cap)
		{
			this->cap = this->cap << 1 ?: 1;
			this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
		}
		
		this->data[this->n++] = b;
		
		changed = true;
	}
	#endif
	
	dpvb(changed);
	
	EXIT;
	return changed;
}

