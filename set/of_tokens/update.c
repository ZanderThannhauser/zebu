
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "struct.h"
#include "update.h"

bool tokenset_update(struct tokenset* this, struct tokenset* them)
{
	ENTER;
	
	bool changed = false;
	
	unsigned i = 0, n = this->n;
	unsigned j = 0, m = them->n;
	
	unsigned  new_cap = this->n + them->n;
	unsigned  new_n = 0;
	#ifdef WTIH_ARENAS
	unsigned* new_data = arena_malloc(this->arena, sizeof(*new_data) * new_cap);
	#else
	unsigned* new_data = malloc(sizeof(*new_data) * new_cap);
	#endif
	
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
		#ifdef WITH_ARENAS
		arena_dealloc(this->arena, this->data);
		#else
		free(this->data);
		#endif
		
		this->data = new_data;
		this->n = new_n;
		this->cap = new_cap;
	}
	else
	{
		#ifdef WITH_ARENAS
		arena_dealloc(this->arena, new_data);
		#else
		free(new_data);
		#endif
	}
	
	EXIT;
	return changed;
}













