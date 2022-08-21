
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "update.h"

bool tokenset_update(struct tokenset* this, struct tokenset* them)
{
	TODO;
	#if 0
	bool changed = false;
	
	unsigned i = 0, n = this->n;
	unsigned j = 0, m = them->n;
	
	unsigned  new_cap = this->n + them->n;
	unsigned  new_n = 0;
	unsigned* new_data = smalloc(sizeof(*new_data) * new_cap);
	
	while (i < n && j < m)
	{
		unsigned a = this->data[i], b = them->data[j];
		
		if (a < b)
			new_data[new_n++] = a, i++;
		else if (b < a)
			new_data[new_n++] = them->data[j++], changed = true;
		else
			new_data[new_n++] = a, i++, j++;
	}
	
	while (i < n) new_data[new_n++] = this->data[i++];
	
	if (j < m)
	{
		changed = true;
		do new_data[new_n++] = them->data[j++]; while (j < m);
	}
	
	if (changed)
	{
		free(this->data);
		
		this->data = new_data;
		this->n = new_n;
		this->cap = new_cap;
	}
	else
	{
		free(new_data);
	}
	
	return changed;
	#endif
}













