
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include <debug.h>

#include "struct.h"
#include "update.h"

void gegexset_update(struct gegexset* this, struct gegexset* them)
{
	ENTER;
	
	TODO;
	#if 0
	unsigned cap = this->n + them->n;
	dpv(cap);
	
	struct gegex** data = smalloc(sizeof(*data) * cap);
	
	bool changed = false;
	
	unsigned n = 0;
	
	struct {
		unsigned i, n;
	} a = {0, this->n}, b = {0, them->n};
	
	while (a.i < a.n && b.i < b.n)
	{
		struct gegex* ae = this->data[a.i], *be = them->data[b.i];
		
		if (ae < be)
			data[n++] = ae, a.i++;
		else if (ae > be)
		{
			changed = true;
			data[n++] = be, b.i++;
		}
		else
		{
			TODO;
		}
	}
	
	while (a.i < a.n)
	{
		data[n++] = this->data[a.i++];
	}
	
	if (b.i < b.n)
	{
		changed = true;
		do data[n++] = them->data[b.i++]; while (b.i < b.n);
	}
	
	if (changed)
	{
		free(this->data);
		
		this->data = data;
		this->cap = cap;
		this->n = n;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	#endif
}














