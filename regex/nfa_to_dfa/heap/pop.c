
#include <debug.h>

#include "../iterator/compare.h"

#include "struct.h"
#include "pop.h"

struct iterator* heap_pop(struct heap* this)
{
	ENTER;
	
	assert (this->n);
	
	struct iterator* retval = this->data[0], *swap;
	
	if (--this->n)
	{
		unsigned l, r, smallest, i = 0;
		struct iterator** const iterators = this->data;
		
		iterators[0] = iterators[this->n];
		
		again: l = 2 * i + 1, r = l + 1, smallest = i;
		
		if (l < this->n && compare_iterators(iterators[l], iterators[i]) < 0)
			smallest = l;
		
		if (r < this->n && compare_iterators(iterators[r], iterators[smallest]) < 0)
			smallest = r;
		
		if (smallest != i)
		{
			swap = iterators[i];
			iterators[i] = iterators[smallest];
			iterators[smallest] = swap;
			
			i = smallest;
			
			goto again; // forgive my father for I have sinned.
		}
	}
	
	EXIT;
	return retval;
}


