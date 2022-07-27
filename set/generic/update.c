
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "update.h"

bool set_update(struct set* this, struct set* them)
{
	bool changed = false;
	ENTER;
	
	TODO;
	#if 0
	unsigned i = 0, n = this->n;
	unsigned j = 0, m = them->n;
	
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

