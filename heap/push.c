
#include <debug.h>

#include "struct.h"
#include "push.h"

void heap_push(struct heap* this, void* new)
{
	ENTER;
	
	if (this->n + 1 > this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	size_t i;
	void** const data = this->data, *swap;
	
	data[this->n] = new;
	
	for (i = this->n; i > 0 && this->cmp(data[i / 2], data[i]) > 0; i >>= 1)
	{
		swap = data[i];
		data[i] = data[i / 2];
		data[i / 2] = swap;
	}
	
	this->n++;
	
	EXIT;
}

