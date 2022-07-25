
#include <debug.h>

#include <assert.h>

#include "struct.h"
#include "pop.h"

void* heap_pop(struct heap* this)
{
	ENTER;
	
	assert (this->n);
	
	void* retval = this->data[0], *swap;
	
	if (--this->n)
	{
		unsigned l, r, smallest, i = 0;
		void** const data = this->data;
		
		data[0] = data[this->n];
		
		again: l = 2 * i + 1, r = 2 * i + 2, smallest = i;
		
		dpv(i);
		
		if (l < this->n && this->cmp(data[l], data[i]) < 0)
			smallest = l;
		
		if (r < this->n && this->cmp(data[r], data[smallest]) < 0)
			smallest = r;
		
		dpv(smallest);
		
		if (smallest != i)
		{
			swap = data[i];
			data[i] = data[smallest];
			data[smallest] = swap;
			
			i = smallest;
			
			goto again; // forgive my father for I have sinned.
		}
	}
	
	EXIT;
	return retval;
}

