
#include <debug.h>

/*#include <memory/srealloc.h>*/

#include "struct.h"
#include "push.h"

void heap_push(struct heap* this, void* new)
{
	ENTER;
	
	TODO;
	#if 0
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	size_t i = this->n++, j;
	void** const data = this->data, *swap;
	
	data[i] = new;
	
	for (; i > 0 && this->cmp(data[j = (i - 1) / 2], data[i]) > 0; i = j)
	{
		swap = data[i];
		data[i] = data[j];
		data[j] = swap;
	}
	#endif
	
	EXIT;
}

